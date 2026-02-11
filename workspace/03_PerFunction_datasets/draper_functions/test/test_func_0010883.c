gsfwrd (struct gscmn *pcmn) {
struct gsvar *pvar;
char *ch, *res;
gaint ret, ntype, wnum, i, len;
gaint lwnum;
gadouble v;

  pcmn->rres = NULL;


  pvar = pcmn->farg;
  if (pvar==NULL) {
    printf ("Error in subwrd:  1st argument missing\n");
    ret = 1;
    goto retrn;
  }
  pvar = pvar->forw;
  if (pvar==NULL) {
    printf ("Error in subwrd:  2nd argument missing\n");
    ret = 1;
    goto retrn;
  }
  gsnum (pvar->strng, &ntype, &lwnum, &v);
  wnum = lwnum;
  if (ntype!=1 || wnum<1) {
    printf ("Error in subwrd:  2nd argument invalid.\n");
    ret = 1;
    goto retrn;
  }


  pvar = pcmn->farg;
  ch = pvar->strng;
  i = 0;
  while (*ch) {
    if (*ch==' '||*ch=='\n'||*ch=='\t'||i==0) {
      while (*ch==' '||*ch=='\n'||*ch=='\t') ch++;
      if (*ch) i++;
      if (i==wnum) break;
    } else ch++;
  }


  len = 0;
  while (*(ch+len)!='\0' && *(ch+len)!=' '
         && *(ch+len)!='\t' && *(ch+len)!='\n') len++;


  res = (char *)malloc(len+1);
  if (res==NULL) {
    printf ("Error:  Storage allocation error\n");
    ret = 1;
    goto retrn;
  }


  for (i=0; i<len; i++) *(res+i) = *(ch+i);
  *(res+len) = '\0';

  ret = 0;
  pcmn->rres = res;


retrn:

  gsfrev (pcmn->farg);
  pcmn->farg = NULL;
  return (ret);
}
