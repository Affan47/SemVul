haz_sph_int(lf,dfx,cf,h,r1)
lfit *lf;
double *dfx, *cf, h, *r1;
{ double s, t0, t1, wt, th;
  INT dim, j, p, *mi;
  mi = lf->mi;
  s = 0; p = mi[MP];
  dim = mi[MDIM];
  for (j=1; j<dim; j++) s += SQR(dfx[j]/(h*lf->sca[j]));
  if (s>1) return(0);

  setzero(r1,p*p);
  t1 = sqrt(1-s)*h*lf->sca[0];
  t0 = -t1;
  if (t0<ilim[0])   t0 = ilim[0];
  if (t1>ilim[dim]) t1 = ilim[dim];
  if (t1>dfx[0]) t1 = dfx[0];
  if (t1<t0) return(0);


  for (j=0; j<=mi[MMINT]; j++)
  { dfx[0] = t0+(t1-t0)*j/mi[MMINT];
    wt = weight(lf,dfx,NULL,h,0,0.0);
    fitfun(lf,dfx,NULL,ff,NULL,0);
    th = innerprod(cf,ff,p);
    if (mi[MLINK]==LLOG) th = exp(th);
    wt *= 2+2*(j&1)-(j==0)-(j==mi[MMINT]);
    addouter(r1,ff,ff,p,wt*th);
  }
  multmatscal(r1,(t1-t0)/(3*mi[MMINT]),p*p);

  return(1);
}
