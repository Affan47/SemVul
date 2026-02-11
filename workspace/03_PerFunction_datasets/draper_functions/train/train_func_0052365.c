__cnvt_param_stkval(struct xstk_t *xsp, struct expr_t *xrhs,
 struct net_t *np, char *innam)
{
 char s1[RECLEN];


 if (!np->n_isaparam) __arg_terr(__FILE__, __LINE__);


 if (np->ntyp == N_REAL)
  {
   if (!xrhs->is_real)
    {
     if (xrhs->szu.xclen == WBITS && xrhs->has_sign) strcpy(s1, "integer");
     else sprintf(s1, "%d bit register", xrhs->szu.xclen);
     __gfinform(486, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
      "parameter %s in %s assign required conversion from %s to real",
      np->nsym->synam, innam, s1);

     __cnv_stk_fromreg_toreal(xsp, (xrhs->has_sign == 1));
    }
  }
 else
  {

   if (xrhs->is_real)
    {
     if (np->nwid == WBITS && np->n_signed) strcpy(s1, "integer");
     else sprintf(s1, "%d bit register", np->nwid);

     __gfinform(487, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
      "parameter %s in %s assign required conversion from real to %s",
      np->nsym->synam, innam, s1);

     __cnv_stk_fromreal_toreg32(xsp);
    }

   if (xsp->xslen != xrhs->szu.xclen)
    {
     __gfinform(488, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
      "parameter %s in %s assign width mismatch was %d new %d - widest used",
      np->nsym->synam, innam, xsp->xslen, np->nwid);


     if (xsp->xslen < np->nwid)
      {
       if (xrhs->has_sign) __sgn_xtnd_widen(xsp, np->nwid);
       else __sizchg_widen(xsp, np->nwid);
      }
    }
  }
}
