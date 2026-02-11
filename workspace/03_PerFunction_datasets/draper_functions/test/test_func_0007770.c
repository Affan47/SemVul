suf_add (const char * word, int len, struct affent * ep, int num)
{
    struct affent *     aent;
    int	                tlen;
    int			cond;
    unsigned char *	cp;
    int			i;
    char	        tword[MAX_WD_LEN];
    char *              pp;

    for (aent = ep, i = num; i > 0; aent++, i--) {


      if ((len > aent->stripl) && (len >= aent->numconds)) {
	cp = (unsigned char *) (word + len);
	for (cond = aent->numconds;  --cond >= 0;  ) {
	    if ((aent->conds[*--cp] & (1 << cond)) == 0) break;
	}
	if (cond < 0) {

          strcpy(tword,word);
          tlen = len;
	  if (aent->stripl) {
             tlen -= aent->stripl;
          }
          pp = (tword + tlen);
          if (aent->appndl) {
	       strcpy (pp, aent->appnd);
	       tlen += aent->stripl;
	  } else *pp = '\0';

          if (numwords < MAX_WORDS) {
              wlist[numwords].word = mystrdup(tword);
              wlist[numwords].pallow = (aent->xpflg & XPRODUCT);
              numwords++;
          }
	}
      }
    }
}
