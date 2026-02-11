compute_phis(const double &dx, const double &dy,
                                 const double &dz)
{
  double delx,dely,delz;

  for (int nu = nlower; nu <= nupper; nu++) {
    delx = dx + double(nu);
    dely = dy + double(nu);
    delz = dz + double(nu);

    phi1d[0][nu] = compute_phi(delx);
    phi1d[1][nu] = compute_phi(dely);
    phi1d[2][nu] = compute_phi(delz);
  }
}
