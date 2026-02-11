unpack_border(int n, int first, double *buf)
{
  int i,j,m,last;
  double *shape,*quat;

  m = 0;
  last = first + n;
  for (i = first; i < last; i++) {
    if (i == nmax) grow(0);
    x[i][0] = buf[m++];
    x[i][1] = buf[m++];
    x[i][2] = buf[m++];
    tag[i] = static_cast<int> (buf[m++]);
    type[i] = static_cast<int> (buf[m++]);
    mask[i] = static_cast<int> (buf[m++]);
    ellipsoid[i] = static_cast<int> (buf[m++]);
    if (ellipsoid[i] == 0) ellipsoid[i] = -1;
    else {
      j = nlocal_bonus + nghost_bonus;
      if (j == nmax_bonus) grow_bonus();
      shape = bonus[j].shape;
      quat = bonus[j].quat;
      shape[0] = buf[m++];
      shape[1] = buf[m++];
      shape[2] = buf[m++];
      quat[0] = buf[m++];
      quat[1] = buf[m++];
      quat[2] = buf[m++];
      quat[3] = buf[m++];
      bonus[j].ilocal = i;
      ellipsoid[i] = j;
      nghost_bonus++;
    }
  }

  if (atom->nextra_border)
    for (int iextra = 0; iextra < atom->nextra_border; iextra++)
      m += modify->fix[atom->extra_border[iextra]]->
        unpack_border(n,first,&buf[m]);
}
