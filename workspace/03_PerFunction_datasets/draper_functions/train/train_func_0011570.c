IntForward(real lat, real lon, real h,
                                  real& x, real& y, real& z,
                                  real M[dim2_]) const throw() {
    real xc, yc, zc;
    _earth.IntForward(lat, lon, h, xc, yc, zc, M);
    xc -= _x0; yc -= _y0; zc -= _z0;
    x = _r[0] * xc + _r[3] * yc + _r[6] * zc;
    y = _r[1] * xc + _r[4] * yc + _r[7] * zc;
    z = _r[2] * xc + _r[5] * yc + _r[8] * zc;
    if (M)
      MatrixMultiply(M);
  }
