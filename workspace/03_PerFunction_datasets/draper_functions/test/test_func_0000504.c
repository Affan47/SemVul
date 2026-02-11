step_exec_stmt(register struct st_t *stp)
{

 for (;;)
  {


   if (__step_from_thread) stp = __brktr_exec_1stmt(stp);
   else __step_from_thread = TRUE;


   if (__pending_enter_iact && __iact_reason == IAER_BRKPT)
    {
     __single_step = FALSE;
     __step_rep_cnt = 0;
     __step_match_itp = NULL;
     __verbose_step = FALSE;


     if (stp == NULL || __cur_thd == NULL) __misc_terr(__FILE__, __LINE__);

     __last_stepitp = __cur_thd->th_itp;
     __last_steptskp = __cur_thd->assoc_tsk;
     __last_stepifi = (int32) stp->stfnam_ind;
     __step_lini = stp->stlin_cnt;
     __step_ifi = (int32) stp->stfnam_ind;

     __stmt_suspend = TRUE;
     suspend_curthd(stp);
     return;
    }

   if (stp == NULL)
    {
     if (!__stmt_suspend)
      { __step_lini = -1; __step_ifi = -1; __cur_thd->thnxtstp = NULL; }
     return;
    }


   if (__step_match_itp != NULL && __inst_ptr != __step_match_itp)
    continue;

   if (stp->stlin_cnt == __step_lini && (int32) stp->stfnam_ind == __step_ifi)
    continue;

   break;
  }


 __step_lini = stp->stlin_cnt;
 __step_ifi = (int32) stp->stfnam_ind;

 if (stepped_to_new_loc(stp))
  {
   __last_stepitp = __inst_ptr;
   __last_steptskp = __cur_thd->assoc_tsk;
   __last_stepifi = (int32) stp->stfnam_ind;


   __cvsim_msg("%s (%s line %d)", __msg_blditree(__xs, __last_stepitp,
    __last_steptskp), __in_fils[__last_stepifi], stp->stlin_cnt);
   if (__last_brktime != __simtime)
    {
     __cvsim_msg(" time %s\n", __to_timstr(__xs, &__simtime));
     __last_brktime = __simtime;
    }
   else __cvsim_msg("\n");
  }

 if (__verbose_step)
  __prt_src_lines((int32) stp->stfnam_ind, stp->stlin_cnt, stp->stlin_cnt);
 __single_step = FALSE;

 if (__step_rep_cnt <= 1) __step_match_itp = NULL;
 __verbose_step = FALSE;
 suspend_curthd(stp);

 signal(SIGINT, SIG_IGN);

 __pending_enter_iact = TRUE;
 __iact_reason = IAER_STEP;
}
