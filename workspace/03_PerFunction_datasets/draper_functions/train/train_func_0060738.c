rd_edgepair_list(FILE *f)
{
 int32 first_time;

 for (first_time = TRUE;;)
  {
   get_sdftok(f);
   if (__toktyp == RPAR)
    {
     if (first_time) goto bad_edgepair;
     break;
    }
   if (__toktyp != LPAR)
    {
bad_edgepair:
     __pv_ferr(1358, "bad tenv_def (WAVEFORM edgelist - %s read",
      prt_sdftok());
     return(FALSE);
    }
   first_time = FALSE;
   get_sdftok(f);
   if (__toktyp != SDF_NEGEDGE && __toktyp != SDF_POSEDGE) goto bad_edgepair;

   get_sdftok(f);
   if (__toktyp != REALNUM && __toktyp != NUMBER) goto bad_edgepair;

   get_sdftok(f);
   if (__toktyp == RPAR) continue;
   if (__toktyp != REALNUM && __toktyp != NUMBER)
    {
bad_elend:
     formend_err("edgelist");
     return(FALSE);
    }
   get_sdftok(f);
   if (__toktyp != RPAR) goto bad_elend;
  }
 return(TRUE);
}
