weightsph(lf,u,h,hasdi,di)
lfit *lf;
double *u, h, di;
INT hasdi;
{ INT i;

  if (!hasdi) di = rho(u,lf->sca,lf->mi[MDIM],lf->mi[MKT],lf->sty);

  for (i=0; i<lf->mi[MDIM]; i++)
  { if ((lf->sty[i]==STLEFT) && (u[i]>0.0)) return(0.0);
    if ((lf->sty[i]==STRIGH) && (u[i]<0.0)) return(0.0);
  }
  if (h==0) return((di==0.0) ? 1.0 : 0.0);

  return(W(di/h,lf->mi[MKER]));
}
