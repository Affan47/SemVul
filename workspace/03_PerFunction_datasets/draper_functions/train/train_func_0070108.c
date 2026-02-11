critval(k0,m,d,al,it,s,nu)
double *k0, al, nu;
INT m, d, it, s;
{ double c, cn, c0, c1, tp, td;
  INT j;
  if (m<0) ERROR(("critval: no terms?"));
  if (m>d+1) m = d+1;
  if ((al<=0) | (al>=1)) ERROR(("critval: invalid alpha %8.5f",al));
  if (lf_error) return(0.0);
  if (al>0.5) WARN(("critval: A mighty large tail probability al=%8.5f",al));
  if (s==1) al = 2*al;
  if (m==0) { d = 0; k0[0] = 1; m = 1; }
  c = 2.0; c0 = 0.0; c1 = 0.0;
  for (j=0; j<it; j++)
  { tp = tailp(c,k0,m,d,nu)-al;
    td = taild(c,k0,m,d,nu);
    if (tp>0) c0 = c;
    if (tp<0) c1 = c;
    cn = c - tp/td;
    if (cn<c0) cn = (c+c0)/2;
    if ((c1>0.0) && (cn>c1)) cn = (c+c1)/2;
    c = cn;
    if (fabs(tp/al)<1.0e-10) return(c);
  }
  return(c);
}
