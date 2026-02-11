gsflin (struct gscmn *pcmn) {
struct gsvar *pvar;
char *ch, *res;
gaint ret, ntype, lnum, i, len;
gaint llnum;
gadouble v;

  pcmn->rres = NULL;


  pvar = pcmn->farg;
  if (pvar==NULL) {
    printf ("Error in sublin:  1st argument missing\n");
    ret = 1;
    goto retrn;
  }
  pvar = pvar->forw;
  if (pvar==NULL) {
    printf ("Error in sublin:  2nd argument missing\n");
    ret = 1;
    goto retrn;
  }
  gsnum (pvar->strng, &ntype, &llnum, &v);
  lnum = llnum;
  if (ntype!=1 || lnum<1) {
    printf ("Error in sublin:  2nd argument invalid.\n");
    ret = 1;
    goto retrn;
  }


  pvar = pcmn->farg;
  ch = pvar->strng;
  i = 1;
  while (*ch && i<lnum) {
    if (*ch=='\n') i++;
    ch++;
  }


  len = 0;
  while (*(ch+len)!='\0' && *(ch+len)!='\n') len++;


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
