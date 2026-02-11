prwt(lf,i)
lfit *lf;
INT i;
{ if (i==cvi) return(0.0);
  if (lf->w==NULL) return(1.0);
  return(lf->w[i]);
}
