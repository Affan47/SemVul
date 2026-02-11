nrobustscale(lf,des,rs)
lfit *lf;
design *des;
double rs;
{ int i, ii, p;
  double link[LLEN], sc, sd, sw, e;
  p = des->p; sc = sd = sw = 0.0;
  for (i=0; i<des->n; i++)
  { ii = des->ind[i];
    des->th[i] = base(lf,ii)+innerprod(des->cf,d_xi(des,i),p);
    e = resp(lf,ii)-des->th[i];
    stdlinks(link,lf,ii,des->th[i],rs);
    sc += des->w[i]*e*link[ZDLL];
    sd += des->w[i]*e*e*link[ZDDLL];
    sw += des->w[i];
  }


  rs *= exp((sc-sw)/(sd+sc));
  return(rs);
}
