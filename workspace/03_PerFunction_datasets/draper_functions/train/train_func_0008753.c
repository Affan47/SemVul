likeden(coef, lk0, f1, A)
double *coef, *lk0, *f1, *A;
{ double lk, r;
  int i, j, p, rstat;

    lk = 0;
  lf_status = LF_OK;
  p = den_des->p;
  if ((den_lf->mi[MLINK]==LIDENT) && (coef[0] != 0.0)) return(NR_BREAK);
  lf_status = (den_des->itype)(den_des->xev,A,den_des->xtwx.Q,den_lf,coef,den_des->h);
  if (lf_error) lf_status = LF_ERR;
  if (lf_status==LF_BADP)
  { *lk0 = -1.0e300;
    return(NR_REDUCE);
  }
  if (lf_status!=LF_OK) return(NR_BREAK);
  if (den_lf->mi[MDEB]>2) prresp(coef,A,(INT)p);

  den_des->xtwx.p = p;
  rstat = NR_OK;
  switch(den_lf->mi[MLINK])
  { case LLOG:
      r = den_des->ss[0]/A[0];
      coef[0] += log(r);
      multmatscal(A,r,(INT)p*p);
      A[0] = den_des->ss[0];
      lk = -A[0];
      if (fabs(coef[0]) > 700)
      { lf_status = LF_OOB;
        rstat = NR_REDUCE;
      }
      for (i=0; i<p; i++)
      { lk += coef[i]*den_des->ss[i];
        f1[i] = den_des->ss[i]-A[i];
      }
      break;
    case LIDENT:
      lk = 0.0;
      for (i=0; i<p; i++)
      { f1[i] = den_des->ss[i];
        for (j=0; j<p; j++)
          den_des->res[i] -= A[i*p+j]*coef[j];
      }
      break;
  }
  *lk0 = den_des->llk = lk;

  return(rstat);
}
