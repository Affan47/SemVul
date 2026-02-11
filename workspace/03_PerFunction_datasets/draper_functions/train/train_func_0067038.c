rcv_make_fixed(NPP *npp, void *_info)
{
      struct make_fixed *info = _info;
      NPPLFE *lfe;
      double lambda;
      if (npp->sol == GLP_SOL)
      {  if (npp->c_stat[info->q] == GLP_BS)
            npp->c_stat[info->q] = GLP_BS;
         else if (npp->c_stat[info->q] == GLP_NS)
         {
            lambda = info->c;
            for (lfe = info->ptr; lfe != NULL; lfe = lfe->next)
               lambda -= lfe->val * npp->r_pi[lfe->ref];

            if (lambda >= 0.0)
               npp->c_stat[info->q] = GLP_NL;
            else
               npp->c_stat[info->q] = GLP_NU;
         }
         else
         {  npp_error();
            return 1;
         }
      }
      return 0;
}
