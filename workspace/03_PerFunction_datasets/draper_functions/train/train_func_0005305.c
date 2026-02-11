onedgaus(cf,mi,resp)
double *cf, *resp;
INT *mi;
{ INT i;
  double f0, mu, s2;
  if (mi[MDEG]>=3)
  { ERROR(("onedgaus only valid for deg=0,1,2"));
    return(LF_ERR);
  }
  if (2*cf[2]>=GFACT*GFACT) return(LF_BADP);

  s2 = 1/(GFACT*GFACT-2*cf[2]);
  mu = cf[1]*s2;
  resp[0] = 1.0;
  if (mi[MDEG]>=1)
  { resp[1] = mu;
    resp[2] = s2+mu*mu;
    if (mi[MDEG]==2)
    { resp[3] = mu*(3*s2+mu*mu);
      resp[4] = 3*s2*s2 + mu*mu*(6*s2+mu*mu);
    }
  }
  f0 = S2PI * exp(cf[0]+mu*mu/(2*s2))*sqrt(s2);
  for (i=0; i<=2*mi[MDEG]; i++) resp[i] *= f0;
  return(LF_OK);
}
