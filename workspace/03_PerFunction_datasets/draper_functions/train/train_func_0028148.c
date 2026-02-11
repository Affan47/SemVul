sncndn(real x, real& sn, real& cn, real& dn)
    const throw() {


    if (_m1 != 0) {
      real mc = _m1;
      real c;
      real m[num_], n[num_];
      unsigned l = 0;
      for (real a = 1; l < num_; ++l) {

        m[l] = a;
        n[l] = mc = sqrt(mc);
        c = (a + mc) / 2;
        if (!(abs(a - mc) > tolJAC_ * a)) {
          ++l;
          break;
        }
        mc = a * mc;
        a = c;
      }
      x = c * x;
      sn = sin(x);
      cn = cos(x);
      dn = 1;
      if (sn != 0) {
        real a = cn / sn;
        c = a * c;
        while (l--) {
          real b = m[l];
          a = c * a;
          c = dn * c;
          dn = (n[l] + a) / (b + a);
          a = c / b;
        }
        a = 1 / sqrt(c * c + 1);
        sn = sn < 0 ? -a : a;
        cn = c * sn;
      }
    } else {
      sn = tanh(x);
      dn = cn = 1 / cosh(x);
    }
  }
