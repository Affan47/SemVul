qpf(real ep2) throw() {


    if (abs(ep2) > real(0.5)) {
      real ep = sqrt(ep2);
      return 3 * (1 + 1 / ep2) * (1 - atan(ep) / ep) - 1;
    } else {
      real ep2n = 1, qp = 0;
      for (int n = 1; ; ++n) {
        ep2n *= -ep2;
        real
          t = ep2n / ((2 * n + 1) * (2 * n + 3)),
          qpn = qp + t;
        if (qpn == qp)
          break;
        qp = qpn;
      }
      qp *= -6;
      return qp;
    }
  }
