pack_q(int n)
{
  double *q = atom->q;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  for (int i = 0; i < nlocal; i++) {
    if (mask[i] & groupbit) vbuf[n] = q[i];
    else vbuf[n] = 0.0;
    n += nvalues;
  }
}
