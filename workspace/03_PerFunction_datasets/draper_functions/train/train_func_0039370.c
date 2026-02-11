arm_event_dctrl(struct delctrl_t *dctp, register word32 *wp,
 int32 wlen)
{
 register i_tev_ndx tevpi;
 struct tev_t *tevp;
 struct st_t *stp;


 alloc_tev_(tevpi, TE_THRD, __inst_ptr, __simtime);

 __cur_thd->thdtevi = tevpi;
 tevp = &(__tevtab[tevpi]);
 tevp->tu.tethrd = __cur_thd;


 if (wp != NULL)
  {
   __cur_thd->th_rhsform = TRUE;
   __cur_thd->th_rhswp = wp;
   __cur_thd->th_rhswlen = wlen;
  }

 if (__debug_flg && __st_tracing)
  {
   stp = tevp->tu.tethrd->thnxtstp;
   __tr_msg("-- arming event thread %s itree loc. %s statement at %s\n",
    __cur_thd->th_itp->itip->isym->synam, __inst_ptr->itip->isym->synam,
    __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt));
  }


 if (dctp->dceschd_tevs[__inum] != -1)
  {
   if (__cur_thd->assoc_tsk == NULL)
    {
     stp = tevp->tu.tethrd->thnxtstp;
     __sgfwarn(635,
      "INTERNAL BUG? - in %s cancel and rearm of event control to resume at %s",
      __msg2_blditree(__xs, __inst_ptr), __bld_lineloc(__xs2, stp->stfnam_ind,
      stp->stlin_cnt));
    }
   else
    {
     stp = tevp->tu.tethrd->thnxtstp;
     __sgfwarn(635,
      "when reexecuting task %s cancel and rearm of event control to resume at %s",
      __msg_blditree(__xs, __inst_ptr, __cur_thd->assoc_tsk),
      __bld_lineloc(__xs2, stp->stfnam_ind, stp->stlin_cnt));
    }
  }


 if (__cur_thd->th_dctp != NULL) __misc_terr(__FILE__, __LINE__);


 dctp->dceschd_tevs[__inum] = tevpi;
 __cur_thd->th_dctp = dctp;

 if (__ev_tracing)
  {
   char vs2[10];

   stp = tevp->tu.tethrd->thnxtstp;
   if (wp == NULL) strcpy(vs2, ""); else strcpy(vs2, "(rhs)");
   __tr_msg("-- event control suspend%s to resume line %s\n",
    vs2, __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt));
  }
}
