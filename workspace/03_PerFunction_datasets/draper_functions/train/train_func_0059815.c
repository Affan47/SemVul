E(real sn, real cn, real dn) const throw() {
    real
      cn2 = cn * cn, dn2 = dn * dn, sn2 = sn * sn,

      ei = abs(sn) * (RF(cn2, dn2, real(1)) -
                      (_m / 3) * sn2 * RD(cn2, dn2, real(1)));

    if (cn < 0) {
      ei = 2 * E() - ei;
    }
    if (sn < 0)
      ei = -ei;
    return ei;
  }
