bld_tfmt_val(char *s, struct expr_t *xp, word32 *ap, word32 *bp,
 int32 blen, int32 trim, int32 fmt_pos)
{
 int32 unit;
 word64 usertim;
 double d1;
 struct mod_t *mdp;
 char s1[RECLEN];

 if (fmt_pos == -1) strcpy(s1, ""); else sprintf(s1, " (pos. %d)", fmt_pos);

 if (xp->is_real) memcpy(&d1, ap, sizeof(double));
 else
  {
   if (blen <= WBITS)
    { if (bp[0] != 0L) return(FALSE); d1 = (double) ap[0]; }
   else
    {

     if (bp[1] != 0L || bp[0] != 0L) return(FALSE);

     usertim = ((word64) ap[0]) | (((word64) ap[1]) << 32);
     if (!__v64_to_real(&d1, &usertim))
      __sgfwarn(572,
       "%%t or $timeformat%s conversion to real lost precision",
      s1);
    }
  }


 mdp = __inst_mod;
 if (mdp->mtime_units != __tfmt_units)
  {
   if (mdp->mtime_units > __tfmt_units)
    {

     unit = mdp->mtime_units - __tfmt_units;
     d1 /= __dbl_toticks_tab[unit];
    }
   else
    {

     unit = __tfmt_units - mdp->mtime_units;
     d1 *= __dbl_toticks_tab[unit];
    }
  }


 if (!trim)
  {
   sprintf(s, "%*.*f%s", (int32) (__tfmt_minfwid - strlen(__tfmt_suf)),
    (int32) __tfmt_precunits, d1, __tfmt_suf);
  }
 else sprintf(s, "%.*f%s", (int32) __tfmt_precunits, d1, __tfmt_suf);
 return(TRUE);
}
