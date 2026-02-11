tftostrenval(char *s, int32 *bitlen)
{
 register int32 bi;
 int32 blen, done, stval;
 byte *sbp;
 struct xstk_t *xsp;
 char *chp, *chp2, s1[4];


 *bitlen = 0;
 for (blen = 0, chp = s;;)
  {
   while (isspace(*chp)) chp++;
   if (*chp == '\0') break;
   blen++;
   while (!isspace(*chp)) { if (*chp == '\0') goto strend; else chp++; }
  }
strend:

 if (blen == 0) return(NULL);
 push_xstk_(xsp, 4*blen);
 sbp = (byte *) xsp->ap;
 for (chp = s, done = FALSE, bi = blen - 1;;)
  {
   while (isspace(*chp)) chp++;
   if (*chp == '\0') break;
   chp2 = chp;
   while (!isspace(*chp))
    { if (*chp == '\0') { done = TRUE; break; } else chp++; }
   if (chp - chp2 != 3) return(NULL);
   strncpy(s1, chp2, 3);
   s1[3] = '\0';
   if ((stval = to_stval(s1)) == -1) {__pop_xstk(); return(NULL); }
   sbp[bi--] = (byte) stval;
   if (done) break;
  }
 *bitlen = blen;
 return(xsp);
}
