top_sort(glp_graph *G, int num[])
{     glp_arc *a;
      int i, j, cnt, top, *stack, *indeg;

      indeg = xcalloc(1+G->nv, sizeof(int));
      stack = xcalloc(1+G->nv, sizeof(int));


      top = 0;
      for (i = 1; i <= G->nv; i++)
      {  num[i] = indeg[i] = 0;
         for (a = G->v[i]->in; a != NULL; a = a->h_next)
            indeg[i]++;
         if (indeg[i] == 0)
            stack[++top] = i;
      }

      cnt = 0;
      while (top > 0)
      {
         i = stack[top--];

         xassert(indeg[i] == 0);

         xassert(num[i] == 0);
         num[i] = ++cnt;


         for (a = G->v[i]->out; a != NULL; a = a->t_next)
         {  j = a->head->i;

            xassert(indeg[j] > 0);
            indeg[j]--;
            if (indeg[j] == 0)
               stack[++top] = j;
         }
      }

      xfree(indeg);
      xfree(stack);
      return G->nv - cnt;
}
