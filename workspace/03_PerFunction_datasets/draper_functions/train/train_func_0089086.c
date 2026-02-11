pack_vz(int n)
{
  double **v = atom->v;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  for (int i = 0; i < nlocal; i++) {
    if (mask[i] & groupbit) vbuf[n] = v[i][2];
    else vbuf[n] = 0.0;
    n += nvalues;
  }
}
