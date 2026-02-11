rd_4_vals(FILE *f, char *formnam)
{
 int32 i;
 struct t_vpi_time *vtp = &(__sdf_delp->da[0]);

 for (i = 0; i < 4; i++)
  {
   if (__toktyp != LPAR)
    {
     __pv_ferr(1334, "(%s required rvalue (pos %d) bad - %s read", formnam,
      i, prt_sdftok());
     return(FALSE);
    }
   get_sdftok(f);

   if (!rd_rtriple(f, &(vtp[i]))) return(FALSE);
   get_sdftok(f);
  }
 return(TRUE);
}
