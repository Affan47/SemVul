kalman_update(double *x,
		   int xr,
		   double *p,

		   double *h,


		   double *z,
		   int zr,
		   double *r)

{
  static double k[4], num[4], denom[4], v[4], w[4];
  int pr=xr, pc=xr,
    hr=zr, hc=xr,
    rr=zr, rc=zr,
    kr=xr, kc=zr,
    nr=xr, nc=zr,
    dr=zr, dc=zr,
    vr=xr, vc=1,
    wr=zr, wc=1;


  mat_mul_nt(p,pr,pc, h,hr,hc, num,nr,nc);
  mat_similarity(h,hr,hc, p,pr,pc, denom,dr,dc);
  mat_add(denom,dr,dc, r,rr,rc, denom,dr,dc);
  if (sym_factor(denom,dr,dc, denom,dr,dc))
    return;
  sym_rdiv(num,nr,nc, denom,dr,dc, k,kr,kc);


  mat_mul(h,hr,hc, x,xr,1, w,wr,wc);
  mat_sub(z,zr,1, w,wr,wc, w,wr,wc);
  mat_mul(k,kr,kc, w,wr,wc, v,vr,vc);
  mat_add(x,xr,1, v,vr,vc, x,xr,1);


  mat_one(v,xr,xr);
  mat_mul(k,kr,kc, h,hr,hc, w,xr,xr);
  mat_sub(v,xr,xr, w,xr,xr, w,xr,xr);
  mat_mul(w,xr,xr, p,xr,xr, v,xr,xr);
  mat_copy(v,xr,xr, p,xr,xr);
}
