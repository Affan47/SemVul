tf_asynchoff(void)
{
 int32 rv;

 if (__run_state != SS_SIM)
  {
   rv = bad_nosimtf_err("tf_(i)asynchoff");

   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (__tfrec == NULL)
  {
   rv = bad_notfcontext_err("tf_asynchoff");

   if (rv == TF_NULLPARAM) return(1); else return(0);
  }


 if (__tfrec->asynchon[__inum]) return(0);


 if (__optimized_sim) __dcelst_off(__tfrec->pvcdcep[__inum]);
 else __free_dceauxlst(__tfrec->pvcdcep[__inum], 1);

 __tfrec->pvcdcep[__inum] = NULL;
 __tfrec->asynchon[__inum] = 0;

 return(0);
}
