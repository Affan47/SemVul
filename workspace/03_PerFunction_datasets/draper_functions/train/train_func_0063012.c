atree_split(lf,ce,le,ll,ur)
lfit *lf;
INT *ce;
double *le, *ll, *ur;
{ INT d, vc, i, is;
  double h, hmin, score[MXDIM];
    memset(score, 0, sizeof(score));
  d = lf->mi[MDIM]; vc = 1<<d;

  hmin = 0.0;
  for (i=0; i<vc; i++)
  { h = lf->h[ce[i]];
    if ((h>0) && ((hmin==0)|(h<hmin))) hmin = h;
  }

  is = 0;
  for (i=0; i<d; i++)
  { le[i] = (ur[i]-ll[i])/lf->sca[i];
    if ((lf->sty[i]==STCPAR) || (hmin==0))
      score[i] = 2*(ur[i]-ll[i])/(lf->fl[i+d]-lf->fl[i]);
    else
      score[i] = le[i]/hmin;
    if (score[i]>score[is]) is = i;
  }
  if (lf->dp[DCUT]<score[is]) return(is);
  return(-1);
}
