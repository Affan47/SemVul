xbarint(lf,x,what)
lfit *lf;
double *x;
INT what;
{ INT i, nc;
  double vv[1+MXDIM], f;
  nc = exvval(lf,vv,0,lf->mi[MDIM],what,0);
  f = vv[0];
  if (nc>1)
    for (i=0; i<lf->mi[MDIM]; i++)
      f += vv[i+1]*(x[i]-evptx(lf,0,i));
  return(f);
}
