stacc_downtomdport(register struct expr_t *lhsx,
 register struct expr_t *rhsx, struct itree_t *down_itp)
{
 byte *bp, *sbp;
 struct net_t *lhsnp;
 struct xstk_t *xsp;

 push_xstk_(xsp, 4*rhsx->szu.xclen);
 sbp = (byte *) xsp->ap;
 get_stwire_addr_(bp, rhsx->lu.sy->el.enp);
 memcpy(sbp, bp, rhsx->szu.xclen);


 __push_itstk(down_itp);
 lhsnp = lhsx->lu.sy->el.enp;


 if (lhsnp->frc_assgn_allocated)
  {
   if (!__correct_forced_newwireval(lhsnp, (word32 *) sbp, (word32 *) NULL))
    { __pop_itstk(); __pop_xstk(); return; }
  }
 __chg_st_val(lhsnp, (word32 *) sbp, (word32 *) NULL);
 __pop_xstk();


 __pop_itstk();
}
