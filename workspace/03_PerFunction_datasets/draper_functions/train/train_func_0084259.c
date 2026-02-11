__do_scope_list(void)
{
 register int32 ifi;
 int32 fr_ifi, to_ifi, fr_lini, to_lini, maxlini;
 struct mod_t *mdp;

 if (__scope_tskp != NULL)
  {
   fr_ifi = (int32) __scope_tskp->tsksyp->syfnam_ind;
   fr_lini = __scope_tskp->tsksyp->sylin_cnt;
   to_ifi = __scope_tskp->tsk_last_ifi;
   to_lini =  __scope_tskp->tsk_last_lini;
  }
 else
  {
   mdp = __scope_ptr->itip->imsym->el.emdp;
   fr_ifi = (int32) mdp->msym->syfnam_ind;
   fr_lini = mdp->msym->sylin_cnt;
   to_ifi = mdp->mod_last_ifi;
   to_lini = mdp->mod_last_lini;
  }


 if (fr_ifi == to_ifi)
  {
   __cvsim_msg("  Listing \"%s\" type %s file: %s\n",
    __msg_blditree(__xs, __scope_ptr, __scope_tskp),
    __scope_ptr->itip->imsym->synam, __in_fils[fr_ifi]);
   __prt_src_lines(fr_ifi, fr_lini, to_lini);
   return;
  }

 __cvsim_msg("  File: %s\n", __in_fils[fr_ifi]);
 if ((maxlini = get_lastfillin(fr_ifi)) == -1) return;
 __prt_src_lines(fr_ifi, fr_lini, maxlini);

 for (ifi = fr_ifi + 1; ifi < to_ifi; ifi++)
  {
   __cvsim_msg("  File: %s\n", __in_fils[ifi]);
   if ((maxlini = get_lastfillin(ifi)) == -1) return;
   __prt_src_lines(ifi, 1, maxlini);
  }
 __cvsim_msg("  File: %s\n", __in_fils[to_ifi]);
 __prt_src_lines(to_ifi, 1, to_lini);

}
