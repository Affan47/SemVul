data_atom(double *coord, tagint imagetmp, char **values) {
  int nlocal = atom->nlocal;
  if (nlocal == nmax)
    grow(0);

  tag[nlocal] = atoi(values[0]);
  if (tag[nlocal] <= 0)
    error->one(FLERR,"Invalid atom ID in Atoms section of data file");

  type[nlocal] = atoi(values[1]);
  if (type[nlocal] <= 0 || type[nlocal] > atom->ntypes)
    error->one(FLERR,"Invalid atom type in Atoms section of data file");

  rho[nlocal] = atof(values[2]);
  e[nlocal] = atof(values[3]);
  cv[nlocal] = atof(values[4]);

  x[nlocal][0] = coord[0];
  x[nlocal][1] = coord[1];
  x[nlocal][2] = coord[2];


  image[nlocal] = imagetmp;

  mask[nlocal] = 1;
  v[nlocal][0] = 0.0;
  v[nlocal][1] = 0.0;
  v[nlocal][2] = 0.0;

  vest[nlocal][0] = 0.0;
  vest[nlocal][1] = 0.0;
  vest[nlocal][2] = 0.0;

  de[nlocal] = 0.0;
  drho[nlocal] = 0.0;

  atom->nlocal++;
}
