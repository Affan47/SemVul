__to_gassign_str(char *s, struct expr_t *xp)
{
 struct xstk_t *xsp;
 byte *sbp;

 if (!xp->x_stren)
  {
   xsp = __eval_xpr(xp);
   __regab_tostr(s, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE);
  }
 else
  {
   xsp = __ndst_eval_xpr(xp);
   sbp = (byte *) xsp->ap;
   __st_regab_tostr(s, sbp, xp->szu.xclen);
  }
 __pop_xstk();
 return(s);
}
