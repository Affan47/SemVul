gsstmt (struct gsrecd *recd, struct gscmn *pcmn) {
struct gsvar *pvar;
gaint rc;
char *res, *buf, *tmp;

  res = gsexpr (recd->epos, pcmn);
  if (res==NULL) {
    printf ("  Error occurred on line %i\n",recd->num);
    printf ("  In file %s\n",recd->pfdf->name);
    return(99);
  }


  buf = gagsdo (res, &rc);
  free (res);


  if (rc==-1) {
    if (buf) free(buf);
    return (999);
  }


  pvar = pcmn->fvar;
  tmp = (char *)malloc(6);
  if (tmp==NULL) {
    printf ("Memory allocation error\n");
    if (buf) free (buf);
    return (99);
  }
  snprintf(tmp,5,"%i",rc);
  free (pvar->strng);
  pvar->strng = tmp;

  pvar = pvar->forw;
  if (buf==NULL) {
    tmp = (char *)malloc(1);
    if (tmp==NULL) {
      printf ("Memory allocation error\n");
      return (99);
    }
    *tmp = '\0';
  } else tmp = buf;
  free (pvar->strng);
  pvar->strng = tmp;
  return(0);
}
