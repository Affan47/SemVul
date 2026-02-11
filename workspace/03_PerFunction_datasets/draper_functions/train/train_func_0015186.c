create_atom(int itype, double *coord)
{
  int nlocal = atom->nlocal;
  if (nlocal == nmax) grow(0);

  tag[nlocal] = 0;
  type[nlocal] = itype;
  x[nlocal][0] = coord[0];
  x[nlocal][1] = coord[1];
  x[nlocal][2] = coord[2];
  mask[nlocal] = 1;
  image[nlocal] = ((tagint) IMGMAX << IMG2BITS) |
    ((tagint) IMGMAX << IMGBITS) | IMGMAX;
  v[nlocal][0] = 0.0;
  v[nlocal][1] = 0.0;
  v[nlocal][2] = 0.0;

  radius[nlocal] = 0.5;
  rmass[nlocal] = 4.0*MY_PI/3.0 * radius[nlocal]*radius[nlocal]*radius[nlocal];
  omega[nlocal][0] = 0.0;
  omega[nlocal][1] = 0.0;
  omega[nlocal][2] = 0.0;

  atom->nlocal++;
}
