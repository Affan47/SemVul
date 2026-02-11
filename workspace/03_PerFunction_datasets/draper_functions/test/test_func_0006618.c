findab(double gam)
{ double *coef, f, sl;
  int i, p, nr_stat;

  mm_gam = gam;
  p = mm_lf->mi[MP];


  coef = mm_des->cf;
  for (i=0; i<p; i++) coef[i] = 0.0;
  if (mm_initial(mm_des, mm_lf, mm_des->f1, p, coef))
  { WARN(("findab: initial value divergence"));
    return(0.0);
  }
  else
    mmax(coef, mm_des->oc, mm_des->res, mm_des->f1,
       &mm_des->xtwx, p, mm_lf->mi[MMXIT], CONVTOL, &nr_stat);

  if (nr_stat != NR_OK) return(0.0);

  sl = 0.0;
  for (i=0; i<mm_lf->mi[MN]; i++) sl += fabs(mm_des->w[i])*mm_des->wd[i];

  return(sl-gam);
}
