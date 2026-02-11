post_force_setup(int vflag)
{
  double **f = atom->f;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;


  for (int i = 0; i < nlocal; i++) {
    if (mask[i] & groupbit) {
      f[i][0] += flangevin[i][0];
      f[i][1] += flangevin[i][1];
      f[i][2] += flangevin[i][2];
    }
  }
}
