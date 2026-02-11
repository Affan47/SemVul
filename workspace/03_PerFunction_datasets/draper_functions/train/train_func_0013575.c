procvhatm(des,lf,v)
design *des;
lfit *lf;
INT v;
{ INT k, n;
  double *l;
  n = (ident==0) ? lf->mi[MN] : des->p;
  if ((lf->mi[MKER]!=WPARM) | (!hasparcomp(lf))) k = procvraw(des,lf,v);
  l = (double *)viptr(lf->L,v*n);
  wdiag(lf,des,l,(INT)0,(INT)1,1);
  return(k);
}
