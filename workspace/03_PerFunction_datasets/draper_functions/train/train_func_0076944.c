arm_nbevent_dctrl(struct delctrl_t *dctp, struct xstk_t *xsp,
 struct st_t *stp)
{
 register i_tev_ndx tevp2i;
 i_tev_ndx tevpi;
 struct tev_t *tevp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];


 if (__ev_tracing)
  {
   __evtr_resume_msg();
    __tr_msg(
     "-- arming event control non blocking assign line %s now %s in %s:\n",
     __bld_lineloc(s1, stp->stfnam_ind, stp->stlin_cnt),
     __to_timstr(s3, &__simtime), __msg2_blditree(s2, __inst_ptr));

   __tr_msg("   EVENT TRIGGER ARM NEW VALUE %s\n",
    __xregab_tostr(s1, xsp->ap, xsp->bp, stp->st.spra.lhsx->szu.xclen,
    stp->st.spra.rhsx));
  }

 tevpi = __bld_nb_tev(stp, xsp, __simtime);
 tevp = &(__tevtab[tevpi]);
 tevp->nb_evctrl = TRUE;

 tevp->tu.tenbpa->nbdctp = dctp;
 if ((tevp2i = dctp->dceschd_tevs[__inum]) != -1)
  {

   for (; __tevtab[tevp2i].tenxti != -1; tevp2i = __tevtab[tevp2i].tenxti) ;
   __tevtab[tevp2i].tenxti = tevpi;

   __tevtab[tevpi].tenxti = -1;
  }
 else dctp->dceschd_tevs[__inum] = tevpi;
}
