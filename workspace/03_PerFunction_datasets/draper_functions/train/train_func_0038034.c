_gageCacheProbe(gageContext *ctx, double *grad,
                int *cc, double *gc,
                int x, int y, int z) {
  int hi;

  hi = _gageHash(x, y, z);
  if ( (cc[3*hi + 0] == x) &&
       (cc[3*hi + 1] == y) &&
       (cc[3*hi + 2] == z) ) {

    ELL_3V_COPY(grad, gc + 3*hi);
  } else {

    cc[3*hi + 0] = x;
    cc[3*hi + 1] = y;
    cc[3*hi + 2] = z;
    gageProbe(ctx, x, y, z);
    ELL_3V_COPY(gc + 3*hi, grad);
  }
  return ;
}
