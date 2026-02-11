wxYuv2Rgb(float *r, float *g, float *b, float *y, float *u, float *v, int width, int height) {
  int iwh = height * width;

  for(int i=0; i < iwh; i++) {
    g[i] = (y[i] - COEFF_YR * (u[i] + y[i]) - COEFF_YB * (v[i] +  y[i]) ) / COEFF_YG;
    r[i] = (u[i] + y[i]);
    b[i] = (v[i] + y[i]);
  }
}
