comp_pre_elab_norm_con_ndx(struct net_t *np, struct expr_t *xp,
 int32 fnind, int32 flcnt)
{
 int32 nni1, nni2, biti, biti2, prtxpr_rng_bad;
 struct xstk_t *xsp;

 if (!is_nonis_const_expr(xp)) return(-1);

 xsp = __eval_xpr(xp);

 if (xsp->xslen > WBITS || xsp->bp[0] != 0)
  { __pop_xstk(); return(-1); }
 biti2 = (int32) xsp->ap[0];
 __pop_xstk();


 if (np->nu.ct->nx1 == NULL || np->nu.ct->nx2 == NULL)
  {
   biti = -1;
  }
 else
  {
   nni1 = (int32) __contab[np->nu.ct->nx1->ru.xvi];
   nni2 = (int32) __contab[np->nu.ct->nx2->ru.xvi];


   prtxpr_rng_bad = FALSE;
   if (nni1 >= nni2)
    { if (biti2 > nni1 || biti2 < nni2) prtxpr_rng_bad  = TRUE; }
   else { if (biti2 < nni1 || biti2 > nni2) prtxpr_rng_bad = TRUE; }
   if (prtxpr_rng_bad)
    {
     __gferr(3415, fnind, flcnt,
      "module port expression select range index %d outside net range [%d:%d] - can't fix",
      biti2, nni1, nni2);
     return(-2);
    }

   if (nni1 < 0 || nni2 < 0 || biti2 < 0)
    {
     __gferr(3415, fnind, flcnt, "lllegal negative port declaration range");
     return(-2);
    }
   biti = normalize_ndx_(biti2, nni1, nni2);
  }
 return(biti);
}
