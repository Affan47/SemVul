sep_real_fmt(char *fmtstr, char *chp, int32 trim)
{
 int32 i;
 char *fchp;


 for (fchp = chp, i = 1; ; fchp++, i++)
  {
   switch (*fchp) {
    case 'e': case 'E': case 'f': case 'F': case 'g': case 'G':

     if (i > 10) return(NULL);
     goto got_fmt;
    case '\0': return(NULL);
   }
  }

got_fmt:
 fchp = fmtstr;
 for (;;)
  {
   switch (*chp) {
    case '-': case '+': case ' ': case '#': break;

    case '0': if (trim) return(NULL); break;
    default: goto col_digs;
   }
   *fchp++ = *chp++;
  }

col_digs:

 for (;;) { if (!isdigit(*chp)) break; *fchp++ = *chp++; }
 if (*chp == '.')
  {
   *fchp++ = *chp++;
   for (;;) { if (!isdigit(*chp)) break; *fchp++ = *chp++; }
  }
 switch (*chp) {
  case 'e': case 'E': case 'g': case 'G': case 'f': case 'F': break;
  default: return(NULL);
 }
 *fchp = '\0';

 return(chp);
}
