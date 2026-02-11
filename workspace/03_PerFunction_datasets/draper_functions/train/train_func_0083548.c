prim_rdset_device_del(FILE *f, struct itree_t *itp,
 struct sy_t *tsyp, struct gate_t *ctgp)
{
 int32 first_time, first2_time, ndels, lcnt, sav_lcnt;
 char formnam[RECLEN];

 for (first_time = TRUE;;)
  {
   get_sdftok(f);
   if (!rd_sdf_formtyp(f)) return(FALSE);
   if (__toktyp == RPAR)
    {
     if (first_time)
      {
       __pv_ferr(1333,
        "primitive (DELAY form empty - at least one (ABOSLUTE or (INCREMENT required");
       return(FALSE);
      }
     break;
    }
   if (__toktyp != SDF_ABSOLUTE && __toktyp != SDF_INCREMENT)
    {
     __pv_ferr(1336,
      "primitive instance (ABSOLUTE or (INCREMENT expected - (%s read",
      prt_sdftok());
     return(FALSE);
    }
   first_time = FALSE;
   strcpy(formnam, __token);
   for (first2_time = TRUE;;)
    {
     get_sdftok(f);
     if (!rd_sdf_formtyp(f)) return(FALSE);
     if (__toktyp == RPAR)
      {
       if (first2_time)
        {
         __pv_ferr(1337,
          "(%s form empty - at least one primitive instance (DEVICE form required",
          formnam);
         return(FALSE);
        }
       break;
      }
     lcnt = __lin_cnt;
     if (__toktyp != SDF_DEVICE)
      {
       __pv_ferr(1336,
        "for primitive instance only (DEVICE form allowed - (%s read",
        prt_sdftok());
       return(FALSE);
      }
     first2_time = FALSE;
     get_sdftok(f);
     if (__toktyp != LPAR) { dellst_err(formnam, "DEVICE"); return(FALSE); }
     get_sdftok(f);
     if ((ndels = rd_sdf_dellst(f, "DEVICE")) == -1) return(FALSE);

     __sdf_delp->no_of_delays = ndels;
     if (strcmp(formnam, "INCREMENT") == 0) __sdf_delp->append_flag = TRUE;
     else __sdf_delp->append_flag = FALSE;


     sav_lcnt = __lin_cnt;
     __lin_cnt = lcnt;
     set_device_del(itp, ctgp, tsyp);
     __lin_cnt = sav_lcnt;
    }
  }
 return(TRUE);
}
