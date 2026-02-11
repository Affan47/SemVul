round_heur(glp_tree *T)
{     glp_prob *P = T->mip;

      int n = P->n;
      int i, j, ret;
      double *x;

      x = talloc(1+n, double);
      for (j = 1; j <= n; j++)
      {  GLPCOL *col = P->col[j];
         if (col->kind == GLP_IV)
         {
            x[j] = floor(col->prim + 0.5);
         }
         else if (col->type == GLP_FX)
         {
            x[j] = col->prim;
         }
         else
         {
            ret = 3;
            goto done;
         }
      }

      for (i = 1; i <= T->orig_m; i++)
      {  int type = T->orig_type[i];
         GLPAIJ *aij;
         double sum;
         if (type == GLP_FR)
            continue;

         sum = 0.0;
         for (aij = P->row[i]->ptr; aij != NULL; aij = aij->r_next)
            sum += aij->val * x[aij->col->j];

         if (type == GLP_LO || type == GLP_DB || type == GLP_FX)
         {  if (sum < T->orig_lb[i] - 1e-9)
            {
               ret = 2;
               goto done;
            }
         }

         if (type == GLP_UP || type == GLP_DB || type == GLP_FX)
         {  if (sum > T->orig_ub[i] + 1e-9)
            {
               ret = 2;
               goto done;
            }
         }
      }

      if (glp_ios_heur_sol(T, x) == 0)
      {
         ret = 0;
      }
      else
      {
         ret = 1;
      }
done: tfree(x);
      return ret;
}
