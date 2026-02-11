brent1()
{
  const int ITMAX=100;
  const double CGOLD=0.3819660;
  const double ZEPS=numeric_limits<double>::epsilon()*1.0e-3;
  double d=0.0,etemp;
  double p,q,r,tol1,tol2,xm;
  double e=0.0;
  double tol=0.001;

  xm=0.5*(a_brent+b_brent);
  tol2=2.0*(tol1=tol*fabs(x_brent)+ZEPS);
  if (fabs(x_brent-xm) <= (tol2-0.5*(b_brent-a_brent))) {
    converged = true;
    dx_brent = x_brent;
    return;
  }
  if (fabs(e) > tol1) {
    r=(x_brent-w_brent)*(fx_brent-fv_brent);
    q=(x_brent-v_brent)*(fx_brent-fw_brent);
    p=(x_brent-v_brent)*q-(x_brent-w_brent)*r;
    q=2.0*(q-r);
    if (q > 0.0) p = -p;
    q=fabs(q);
    etemp=e;
    e=d;
    if (fabs(p) >= fabs(0.5*q*etemp) || p <= q*(a_brent-x_brent) || p >= q*(b_brent-x_brent))
      d=CGOLD*(e=(x_brent >= xm ? a_brent-x_brent : b_brent-x_brent));
    else {
      d=p/q;
      dx_brent=x_brent+d;
      if (dx_brent-a_brent < tol2 || b_brent-dx_brent < tol2)
        d=SIGN(tol1,xm-x_brent);
    }
  } else {
    d=CGOLD*(e=(x_brent >= xm ? a_brent-x_brent : b_brent-x_brent));
  }
  dx_brent=(fabs(d) >= tol1 ? x_brent+d : x_brent+SIGN(tol1,d));

  first_brent_pass = false;

  return;
}
