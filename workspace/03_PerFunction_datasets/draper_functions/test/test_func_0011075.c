gra_viewpoint(xf,yf,zf,xt,yt,zt) double xf,yf,zf,xt,yt,zt;
{
  GMATRIX gvm;

  double r1,r2;


  gra_ident(gra_state.viewm);
  gra_state.viewm[3][0] = -xf;
  gra_state.viewm[3][1] = -yf;
  gra_state.viewm[3][2] = -zf;

  xf = xf - xt;
  yf = yf - yt;
  zf = zf - zt;


  gra_ident(gvm);
  gvm[1][2] = -1;
  gvm[2][1] =  1;
  gvm[1][1] =  0;
  gvm[2][2] =  0;
  gra_mult(gra_state.viewm, gvm);

  r1 = sqrt(xf*xf + yf*yf);
  if (r1 != 0)
  {
    gra_ident(gvm);
    gvm[0][0] = -yf/r1;
    gvm[2][2] =  gvm[0][0];
    gvm[0][2] =  xf/r1;
    gvm[2][0] = -gvm[0][2];
    gra_mult(gra_state.viewm,gvm);
  }

  r2 = sqrt(yf*yf + zf*zf);
  if (r2 != 0)
  {
    gra_ident(gvm);
    gvm[1][1] = r1/r2;
    gvm[2][2] = gvm[1][1];
    gvm[1][2] = zf/r2;
    gvm[2][1] = -gvm[1][2];
    gra_mult(gra_state.viewm,gvm);
  }

  gra_ident(gvm);
  gvm[2][2] = -1.0;
  gra_mult(gra_state.viewm,gvm);

  gra_set_transfm();
}
