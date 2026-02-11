dmp_udp_lines(FILE *f, struct udp_t *udpp)
{
 register int32 i;
 register struct utline_t *utlp;
 int32 numins, sav_stlevel;
 char *chp, s1[RECLEN];

 sav_stlevel = __pv_stlevel;
 __pv_stlevel = 4;
 __outlinpos = 0;
 numins = udpp->numins;
 for (utlp = udpp->utlines; utlp != NULL; utlp = utlp->utlnxt)
  {
   for (chp = utlp->tline, i = 0; i < numins; i++, chp++)
    {

     if (utlp->uledinum == i)
      {


       if (utlp->utabsel == '0' && *chp == '1') __wrap_puts("    r", f);
       else if (utlp->utabsel == '1' && *chp == '0') __wrap_puts("    f", f);
       else if (utlp->utabsel == '*') __wrap_puts("    *", f);
       else if (utlp->utabsel == 'p') __wrap_puts("    p", f);
       else if (utlp->utabsel == 'n') __wrap_puts("    n", f);
       else
        {
         sprintf(s1, " (%c%c)", (char) utlp->utabsel, *chp);
         __wrap_puts(s1, f);
        }
      }

     else { sprintf(s1, "%5c", *chp); __wrap_puts(s1, f); }
    }
   if (udpp->utyp != U_COMB)
    { sprintf(s1, " : %c ", *chp); __wrap_puts(s1, f); chp++; }
   sprintf(s1, " : %c ;", *chp);
   __nl_wrap_puts(s1, f);
  }
 __pv_stlevel = sav_stlevel;
}
