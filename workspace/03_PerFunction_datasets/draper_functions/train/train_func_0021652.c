eval_psi(glp_tree *T, int j, int brnch)
{

      struct csa *csa = T->pcost;
      double beta, degrad, psi;
      xassert(csa != NULL);
      xassert(1 <= j && j <= T->n);
      if (brnch == GLP_DN_BRNCH)
      {
         if (csa->dn_cnt[j] == 0)
         {
            beta = T->mip->col[j]->prim;
            degrad = eval_degrad(T->mip, j, floor(beta));
            if (degrad == DBL_MAX)
            {  psi = DBL_MAX;
               goto done;
            }
            csa->dn_cnt[j] = 1;
            csa->dn_sum[j] = degrad / (beta - floor(beta));
         }
         psi = csa->dn_sum[j] / (double)csa->dn_cnt[j];
      }
      else if (brnch == GLP_UP_BRNCH)
      {
         if (csa->up_cnt[j] == 0)
         {
            beta = T->mip->col[j]->prim;
            degrad = eval_degrad(T->mip, j, ceil(beta));
            if (degrad == DBL_MAX)
            {  psi = DBL_MAX;
               goto done;
            }
            csa->up_cnt[j] = 1;
            csa->up_sum[j] = degrad / (ceil(beta) - beta);
         }
         psi = csa->up_sum[j] / (double)csa->up_cnt[j];
      }
      else
         xassert(brnch != brnch);
done: return psi;
}
