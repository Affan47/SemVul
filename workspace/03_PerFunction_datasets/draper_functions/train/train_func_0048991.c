RD(real x, real y, real z) throw() {

    real
      a0 = (x + y + 3 * z)/5,
      an = a0,
      q = max(max(abs(a0-x), abs(a0-y)), abs(a0-z)) / tolRD_,
      x0 = x,
      y0 = y,
      z0 = z,
      mul = 1,
      s = 0;
    while (q >= mul * abs(an)) {

      real ln = sqrt(x0)*sqrt(y0) +
        sqrt(y0)*sqrt(z0) +
        sqrt(z0)*sqrt(x0);
      s += 1/(mul * sqrt(z0) * (z0 + ln ));
      an = (an + ln)/4;
      x0 = (x0 + ln)/4;
      y0 = (y0 + ln)/4;
      z0 = (z0 + ln)/4;
      mul *= 4;
    }
    real
      xx = (a0 - x) / (mul * an),
      yy = (a0 - y) / (mul * an),
      zz = -(xx + yy) / 3,
      e2 = xx * yy - 6 * zz * zz,
      e3 = (3 * xx * yy - 8 * zz * zz)*zz,
      e4 = 3 * (xx * yy - zz * zz) * zz * zz,
      e5 = xx * yy * zz * zz * zz;
    return (1 - 3 * e2 / 14 + e3 / 6 + 9 * e2 * e2 / 88 - 3 * e4 / 22
            - 9 * e2 * e3 / 52 + 3 * e5 / 26) / (mul * an * sqrt(an))
      + 3 * s;
  }
