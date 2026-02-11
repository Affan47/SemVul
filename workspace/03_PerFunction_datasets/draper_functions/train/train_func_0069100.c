pack_quatw(int n)
{
  if (avec_ellipsoid) {
    AtomVecEllipsoid::Bonus *bonus = avec_ellipsoid->bonus;
    int *ellipsoid = atom->ellipsoid;
    int *mask = atom->mask;
    int nlocal = atom->nlocal;

    for (int i = 0; i < nlocal; i++) {
      if ((mask[i] & groupbit) && ellipsoid[i] >= 0)
        buf[n] = bonus[ellipsoid[i]].quat[0];
      else buf[n] = 0.0;
      n += nvalues;
    }

  } else {
    AtomVecBody::Bonus *bonus = avec_body->bonus;
    int *body = atom->body;
    int *mask = atom->mask;
    int nlocal = atom->nlocal;

    for (int i = 0; i < nlocal; i++) {
      if ((mask[i] & groupbit) && body[i] >= 0)
        buf[n] = bonus[body[i]].quat[0];
      else buf[n] = 0.0;
      n += nvalues;
    }
  }
}
