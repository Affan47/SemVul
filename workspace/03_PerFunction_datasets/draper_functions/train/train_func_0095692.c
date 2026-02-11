glp_cpx_basis(glp_prob *lp)
{     if (lp->m == 0 || lp->n == 0)
         glp_std_basis(lp);
      else
         cpx_basis(lp);
      return;
}
