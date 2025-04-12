/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

/// Structura pentru graf
typedef struct Graph {
    int v;              // numărul de noduri
    int *vis;           // vector pentru a marca vizitele
    struct Node **alst; // listele de adiacență
} GPH;

/// Structura pentru stiva
typedef struct Stack {
    int t;      // indexul ultimului element
    int scap;   // capacitatea stivei
    int *arr;   // vector pentru elementele stivei
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s;
}

void push(STK *s, int pshd) {
    if (s->t < s->scap - 1) {
        s->t++;
        s->arr[s->t] = pshd;
    }
}

void DFS(GPH *g, int start) {
    g->vis[start] = 1;

    NODE *aux = g->alst[start];
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr) {
    int src, dest;
    printf("Introdu %d muchii (de la 0 la %d):\n", edg_nr, g->v - 1);

    for (int i = 0; i < edg_nr; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g) {
    for (int i = 0; i < g->v; i++) {
        g->vis[i] = 0;
    }
}

int can_be_reached(GPH *g, int src, int dest) {
    wipe(g);
    DFS(g, src);
    return g->vis[dest];
}

int main() {
    int nrv, edg_nr, src, dest;

    printf("Cate noduri are graful?\n");
    scanf("%d", &nrv);

    printf("Cate muchii are graful?\n");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    insert_edges(g, edg_nr);

    printf("Introdu cele doua restaurante (noduri) pentru a verifica daca exista drum intre ele:\n");
    scanf("%d %d", &src, &dest);

    if (can_be_reached(g, src, dest)) {
        printf("Exista un drum direct intre restaurantele %d si %d.\n", src, dest);
    } else {
        printf("Nu exista un drum direct intre restaurantele %d si %d.\n", src, dest);
    }

    return 0;
}

