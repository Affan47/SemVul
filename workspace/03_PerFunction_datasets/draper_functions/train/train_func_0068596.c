famrbin(y,p,th,link,res,cens,w)
double y, p, th, *res, w;
INT link, cens;
{ double s2y;
  if (link==LINIT)
  { res[ZDLL] = y;
    return(LF_OK);
  }
  if ((y<0) | (y>w))
  { res[ZLIK] = res[ZDLL] = res[ZDDLL] = 0.0;
    return(LF_OK);
  }
  res[ZLIK] = (th<0) ? th*y-w*log(1+exp(th)) : th*(y-w)-w*log(1+exp(-th));
  if (y>0) res[ZLIK] -= y*log(y/w);
  if (y<w) res[ZLIK] -= (w-y)*log(1-y/w);
  res[ZDLL] = (y-w*p);
  res[ZDDLL]= w*p*(1-p);
  if (-res[ZLIK]>HUBERC*HUBERC/2.0)
  { s2y = sqrt(-2*res[ZLIK]);
    res[ZLIK] = HUBERC*(HUBERC/2.0-s2y);
    res[ZDLL] *= HUBERC/s2y;
    res[ZDDLL] = HUBERC/s2y*(res[ZDDLL]-1/(s2y*s2y)*w*p*(1-p));
  }
  return(LF_OK);
}
