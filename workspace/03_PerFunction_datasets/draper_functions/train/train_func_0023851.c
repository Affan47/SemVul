Reverse(real lon0, real x, real y,
                                real& lat, real& lon,
                                real& gamma, real& k)
    const throw() {
    y *= _sign;
    real
      nx = _k0 * _n0 * x, ny = _k0 * _n0 * y, y1 =  _nrho0 - ny,
      den = Math::hypot(nx, y1) + _nrho0,
      drho = den != 0 ? (_k0*x*nx - 2*_k0*y*_nrho0 + _k0*y*ny) / den : 0,

      dsxia = - _scxi0 * (2 * _nrho0 + _n0 * drho) * drho /
              (Math::sq(_a) * _qZ),
      txi = (_txi0 + dsxia) / sqrt(max(1 - dsxia * (2*_txi0 + dsxia), epsx2_)),
      tphi = tphif(txi),
      phi = _sign * atan(tphi),
      theta = atan2(nx, y1),
      lam = _n0 != 0 ? theta / (_k2 * _n0) : x / (y1 * _k0);
    gamma = _sign * theta / Math::degree<real>();
    lat = phi / Math::degree<real>();
    lon = lam / Math::degree<real>();

    if (lon + lon0 >= 180)
      lon += lon0 - 360;
    else if (lon + lon0 < -180)
      lon += lon0 + 360;
    else
      lon += lon0;
    k = _k0 * (den != 0 ? (_nrho0 + _n0 * drho) * hyp(_fm * tphi) / _a : 1);
  }
