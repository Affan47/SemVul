glp_adv_basis(glp_prob *P, int flags)
{     int i, j, k, m, n, min_mn, size, *rn, *cn;
      char *flag;
      if (flags != 0)
         xerror("glp_adv_basis: flags = %d; invalid flags\n", flags);
      m = P->m;
      n = P->n;
      if (m == 0 || n == 0)
      {
         glp_std_basis(P);
         goto done;
      }
      xprintf("Constructing initial basis...\n");

      min_mn = (m < n ? m : n);
      rn = talloc(1+min_mn, int);
      cn = talloc(1+min_mn, int);
      flag = talloc(1+m, char);

      for (i = 1; i <= m; i++)
      {  flag[i] = 0;
         glp_set_row_stat(P, i, GLP_NS);
      }
      for (j = 1; j <= n; j++)
         glp_set_col_stat(P, j, GLP_NS);


#if 1
      size = triang(m, n, mat, P, 0.001, rn, cn);
#endif
      xassert(0 <= size && size <= min_mn);


      for (k = 1; k <= size; k++)
      {  i = rn[k];
         xassert(1 <= i && i <= m);
         flag[i] = 1;
         j = cn[k];
         xassert(1 <= j && j <= n);
         glp_set_col_stat(P, j, GLP_BS);
      }


      for (i = 1; i <= m; i++)
      {  if (flag[i] == 0)
         {  glp_set_row_stat(P, i, GLP_BS);
            if (P->row[i]->type != GLP_FX)
               size++;
         }
      }


      xprintf("Size of triangular part is %d\n", size);

      tfree(rn);
      tfree(cn);
      tfree(flag);
done: return;
}
