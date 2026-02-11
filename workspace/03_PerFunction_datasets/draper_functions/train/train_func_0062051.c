glp_get_mat_col(glp_prob *lp, int j, int ind[], double val[])
{     GLPAIJ *aij;
      int len;
      if (!(1 <= j && j <= lp->n))
         xerror("glp_get_mat_col: j = %d; column number out of range\n",
            j);
      len = 0;
      for (aij = lp->col[j]->ptr; aij != NULL; aij = aij->c_next)
      {  len++;
         if (ind != NULL) ind[len] = aij->row->i;
         if (val != NULL) val[len] = aij->val;
      }
      xassert(len <= lp->m);
      return len;
}
