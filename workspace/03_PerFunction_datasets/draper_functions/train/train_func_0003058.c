build_subgraph(struct csa *csa)
{
      glp_prob *P = csa->P;
      int n = P->n;
      CFG *G = csa->G;
      int *ind = csa->ind;
      int *pos = G->pos;
      int *neg = G->neg;
      int nv = G->nv;
      int *ref = G->ref;
      int *vtoi = csa->vtoi;
      int *itov = csa->itov;
      double *wgt = csa->wgt;
      int j, k, v, w, nn, len;
      double z, sum;

      nn = 0;

      for (v = 1; v <= nv; v++)
      {

         j = ref[v];
         xassert(1 <= j && j <= n);
         if (pos[j] == v)
         {
            z = P->col[j]->prim;
         }
         else if (neg[j] == v)
         {
            z = 1.0 - P->col[j]->prim;
         }
         else
            xassert(v != v);


         if (z < 0.001)
         {  vtoi[v] = 0;
            continue;
         }

         sum = z;

         len = cfg_get_adjacent(G, v, ind);
         for (k = 1; k <= len; k++)
         {
            w = ind[k];
            xassert(w != v);

            j = ref[w];
            xassert(1 <= j && j <= n);
            if (pos[j] == w)
               sum += P->col[j]->prim;
            else if (neg[j] == w)
               sum += 1.0 - P->col[j]->prim;
            else
               xassert(w != w);
         }


         if (sum < 1.010)
         {  vtoi[v] = 0;
            continue;
         }

         nn++;
         vtoi[v] = nn;
         itov[nn] = v;
         wgt[nn] = z;
      }

      csa->nn = nn;
      return;
}
