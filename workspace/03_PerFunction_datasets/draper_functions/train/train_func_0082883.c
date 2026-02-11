chk_putdstr(char *s, int32 base, int32 *len)
{
 register char *chp, *chp2;
 register int32 slen;


 for (*len = 0, slen = 0, chp = s, chp2 = __numtoken; *chp != '\0';)
  {
   if (*chp == '_') { chp++; continue; }
   if (__is_vdigit((int32) *chp, base) < 0) return(FALSE);
   *chp2++ = *chp++;
   slen++;
  }
 *chp2 = '\0';
 *len = slen;
 return(TRUE);
}
