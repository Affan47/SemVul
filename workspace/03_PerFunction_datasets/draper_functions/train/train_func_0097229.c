__vpitime_to_ticks(word64 *timp, p_vpi_time time_p,
 struct mod_t *mdp)
{
 word64 tim;

 if (time_p->type == vpiScaledRealTime)
  {
   if (!__real_to_v64tim(&tim, time_p->real))
    {
     __vpi_err(1926, vpiError,
      "vpiTimeVal type vpiScaledRealTime too large for 64 bit time - not converted");
     *timp = 0ULL;
     return(FALSE);
    }
   if (mdp != NULL && !mdp->mno_unitcnv) cnv_num64to_ticks_(*timp, tim, mdp);
   else *timp = tim;
  }
 else
  {
   if (time_p->type != vpiSimTime)
    {
     __vpi_err(2018, vpiWarning,
      "vpiTimeVal of type vpiSuppressTime meaningless here - using vpiSimTime");
    }


   *timp = ((word64) ((word32) (time_p->low)))
     | (((word64) ((word32) time_p->high)) << 32);
  }
 return(TRUE);
}
