set_shape(int i,
                                 double shapex, double shapey, double shapez)
{
  if (ellipsoid[i] < 0) {
    if (shapex == 0.0 && shapey == 0.0 && shapez == 0.0) return;
    if (nlocal_bonus == nmax_bonus) grow_bonus();
    double *shape = bonus[nlocal_bonus].shape;
    double *quat = bonus[nlocal_bonus].quat;
    shape[0] = shapex;
    shape[1] = shapey;
    shape[2] = shapez;
    quat[0] = 1.0;
    quat[1] = 0.0;
    quat[2] = 0.0;
    quat[3] = 0.0;
    bonus[nlocal_bonus].ilocal = i;
    ellipsoid[i] = nlocal_bonus++;
  } else if (shapex == 0.0 && shapey == 0.0 && shapez == 0.0) {
    copy_bonus(nlocal_bonus-1,ellipsoid[i]);
    nlocal_bonus--;
    ellipsoid[i] = -1;
  } else {
    double *shape = bonus[ellipsoid[i]].shape;
    shape[0] = shapex;
    shape[1] = shapey;
    shape[2] = shapez;
  }
}
