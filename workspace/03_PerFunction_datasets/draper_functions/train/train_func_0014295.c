revert_state()
{
  double **x = atom->x;
  double **v = atom->v;
  tagint *image = atom->image;
  int nlocal = atom->nlocal;

  double **astore = fix_revert->astore;

  for (int i = 0; i < nlocal; i++) {
    x[i][0] = astore[i][0];
    x[i][1] = astore[i][1];
    x[i][2] = astore[i][2];
    v[i][0] = -astore[i][3];
    v[i][1] = -astore[i][4];
    v[i][2] = -astore[i][5];
    image[i] = *((tagint *) &astore[i][6]);
  }
}
