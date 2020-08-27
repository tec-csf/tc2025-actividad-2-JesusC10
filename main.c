/*
Jesús Cesar González Acosta - A01422050
23/08/2020

Recorriendo un arreglo de números enteros utilizando un Forward Iterator.
Recorriendo un arreglo de estructuras del tipo Libro, utilizando un Bidirectional Iterator.
struct  Libro {
  char * titulo;
  int paginas;
}
El iterador debe contener, al menos, las siguientes funcionalidades: 

begin :  Regresa un apuntador al primer elemento 
end : Regresa un apuntador al último elemento
next : Regresa un apuntador al siguiente elemento. Si se llegó al final debe regresar NULL.
prev : Regresa un apuntador al elemento anterior. Si llegó al inicio debe regresar NULL.
Tenga en cuenta que debe existir una función genérica denominada Recorre que debe recibir como parámetros un arreglo de cualquier tipo 
y un iterador de cualquier tipo y debe recorrer el arreglo utilizando el iterador especificado y mostrar el contenido del arreglo.

El problema lo analicé y resolví junto con Julio Villazón.
*/

#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 3

typedef struct
{
  char *title;
  int pages;
} Libro;

typedef void (*p_type)(void *);
typedef void (*t_recorre)(void *, size_t, size_t, p_type);

void recorre(t_recorre, void *, size_t, size_t, p_type);

void forward(void * vector, size_t count, size_t size, p_type print);
void reverse(void *vector, size_t count, size_t size, p_type print);
void bidirectional(void *vector, size_t count, size_t size, p_type print);

void *begin(void *);
void *end(void *, size_t, size_t);
void *next(void *, void *, size_t, size_t);
void *prev(void *, void *, size_t, size_t);

void printAllInt(int *, int);
void printInt(void *);

void printAllFloat(float *, int);
void printFloat(void *);

void printAllStruct(Libro *, int);
void printStruct(void *);

int main (int arc, const char * argv[]){

  int * vector = (int *) malloc(N * sizeof(int));

  int * aux = vector;
  int * last = N + vector;

  for(; aux < last; ++aux){
    *aux = rand() % 100;
  }

  printf("Lista de enteros: \n");
  printAllInt(vector, N);
  printf("\n");

  printf("Fordward: \n");
  recorre(&forward, vector, N, sizeof(*vector), &printInt);
  printf("\n");

  float *vectorf = (float *)malloc(N * sizeof(float));

  float *auxf = vectorf;
  float *lastf = N + vectorf;

  for (; auxf < lastf; ++auxf)
  {
    *auxf = rand() % 100;
  }

  printf("Lista de flotantes: \n");
  printAllFloat(vectorf, N);
  printf("\n");

  printf("Reverse: \n");
  recorre(&reverse, vectorf, N, sizeof(*vectorf), &printFloat);
  printf("\n");

  Libro * lib;
  Libro * aux2;
  Libro * final;

  lib = (Libro *) malloc(M * sizeof(Libro));
  aux2 = lib;
  final = lib + M;

  for (; aux2 < final; ++aux2)
  {
    aux2->pages = rand() % 100;
    aux2->title = (char *) malloc(sizeof(char)*20);
    aux2->title = "Harry Potter";
  }

  printf("Lista de Libros: \n");
  printAllStruct(lib, M);
  printf("\n");

  printf("Bidirectional: \n");
  recorre(&bidirectional, lib, M, sizeof(*lib), &printStruct);
  printf("\n");

  free(vector);
  free(vectorf);
  for (; aux2 < final; ++aux2)
  {
    free(aux2->title);
  }
  free(lib);

    return 0;
}

void recorre(t_recorre algorithm, void * vector, size_t count, size_t size, p_type print){
  (*algorithm)(vector, count, size, print);
}

void forward(void *vector, size_t count, size_t size, p_type print)
{
  void * current = begin(vector);

  do{
    (*print)(current);
    current = next(vector, current, count, size);
  }while(current != NULL);

  printf("\n");
}

void reverse(void *vector, size_t count, size_t size, p_type print)
{
  void *current = end(vector, count, size);

  do
  {
    (*print)(current);
    current = prev(vector, current, count, size);
  } while (current != NULL);

  printf("\n");
}

void bidirectional(void *vector, size_t count, size_t size, p_type print)
{
  forward(vector, count, size, print);
  reverse(vector, count, size, print);
}

void *begin(void *vector){
  return vector;
}

void *end(void *vector, size_t count, size_t size)
{
  return vector + (count*size) - size;
}

void *next(void *vector, void *current, size_t count, size_t size)
{
  void * next = current + size;
  void * final = end(vector, count, size);
  if(next > final)
    return NULL;
  return next;
}

void *prev(void *vector, void *current, size_t count, size_t size)
{
  void *prev = current - size;
  void *start = begin(vector);
  if (prev < start)
    return NULL;
  return prev;
}

void printInt(void * current)
{
  printf(" %3d ", *(int *)current);
}

void printFloat(void * current)
{
  printf(" %3f ", *(float *)current);
}

void printStruct(void * current){
  Libro * aux = (Libro *)current;
  printf("Title: %s,", aux->title);
  printf(" Pages: %d |", aux->pages);
}

void printAllInt(int *vector, int count)
{
  int *aux = vector;
  int *last = vector + count;

  for (; aux < last; ++aux)
  {
    printf(" %3d ", *aux);
  }

  printf("\n");
}

void printAllFloat(float *vector, int count)
{
  float *aux = vector;
  float *last = vector + count;

  for (; aux < last; ++aux)
  {
    printf(" %3f ", *aux);
  }

  printf("\n");
}

void printAllStruct(Libro *vector, int count)
{
  Libro *aux = vector;
  Libro *last = vector + count;

  for (; aux < last; ++aux)
  {
    printf("Title: %s,", aux->title);
    printf(" Pages: %d |", aux->pages);
  }

  printf("\n");
}
