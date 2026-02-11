tr_proc_assign(struct st_t *stp, struct xstk_t *xsp)
{
 struct expr_t *xrhs;

 __cur_sofs = 0;
 __dmp_proc_assgn((FILE *) NULL, stp, (struct delctrl_t *) NULL, FALSE);
 __exprline[__cur_sofs] = 0;
 __trunc_exprline(TRTRUNCLEN, FALSE);
 __tr_msg("trace: %-7d %s", __slin_cnt, __exprline);
 xrhs = stp->st.spra.rhsx;


 if (xrhs->optyp != NUMBER && xrhs->optyp != REALNUM)
  {
   __tr_msg(" [%s]\n", __xregab_tostr(__xs, xsp->ap, xsp->bp, xsp->xslen,
    stp->st.spra.lhsx));
  }
 else __tr_msg("\n");
 __cur_sofs = 0;
}
