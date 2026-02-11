zetainv(real taup, real lam, real& u, real& v)
    const throw()  {
    real
      psi = Math::asinh(taup),
      scal = 1/Math::hypot(real(1), taup);
    if (zetainv0(psi, lam, u, v))
      return;
    real stol2 = tol2_ / Math::sq(max(psi, real(1)));

    for (int i = 0, trip = 0; i < numit_; ++i) {
      real snu, cnu, dnu, snv, cnv, dnv;
      _Eu.sncndn(u, snu, cnu, dnu);
      _Ev.sncndn(v, snv, cnv, dnv);
      real tau1, lam1, du1, dv1;
      zeta(u, snu, cnu, dnu, v, snv, cnv, dnv, tau1, lam1);
      dwdzeta(u, snu, cnu, dnu, v, snv, cnv, dnv, du1, dv1);
      tau1 -= taup;
      lam1 -= lam;
      tau1 *= scal;
      real
        delu = tau1 * du1 - lam1 * dv1,
        delv = tau1 * dv1 + lam1 * du1;
      u -= delu;
      v -= delv;
      if (trip)
        break;
      real delw2 = Math::sq(delu) + Math::sq(delv);
      if (!(delw2 >= stol2))
        ++trip;
    }
  }
