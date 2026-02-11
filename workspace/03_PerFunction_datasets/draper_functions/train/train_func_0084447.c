glp_get_obj_coef(glp_prob *lp, int j)
{     if (!(0 <= j && j <= lp->n))
         xerror("glp_get_obj_coef: j = %d; column number out of range\n"
            , j);
      return j == 0 ? lp->c0 : lp->col[j]->coef;
}
