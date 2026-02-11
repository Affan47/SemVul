SphericalAnomaly(real lat, real lon, real h,
                                      real& Dg01, real& xi, real& eta)
    const throw() {
    real X, Y, Z, M[Geocentric::dim2_];
    _earth.Earth().IntForward(lat, lon, h, X, Y, Z, M);
    real
      deltax, deltay, deltaz,
      T = InternalT(X, Y, Z, deltax, deltay, deltaz, true, false),
      clam = M[3], slam = -M[0],
      P = Math::hypot(X, Y),
      R = Math::hypot(P, Z),

      cpsi = R ? P / R : M[7],
      spsi = R ? Z / R : M[8];

    real MC[Geocentric::dim2_];
    Geocentric::Rotation(spsi, cpsi, slam, clam, MC);
    Geocentric::Unrotate(MC, deltax, deltay, deltaz, deltax, deltay, deltaz);

    Dg01 = - deltaz - 2 * T / R;
    real gammaX, gammaY, gammaZ;
    _earth.U(X, Y, Z, gammaX, gammaY, gammaZ);
    real gamma = Math::hypot( Math::hypot(gammaX, gammaY), gammaZ);
    xi  = -(deltay/gamma) / Math::degree<real>();
    eta = -(deltax/gamma) / Math::degree<real>();
  }
