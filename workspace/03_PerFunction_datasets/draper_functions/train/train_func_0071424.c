pack_yu(int n)
{
  double **x = atom->x;
  tagint *image = atom->image;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  double yprd = domain->yprd;

  for (int i = 0; i < nlocal; i++) {
    if (mask[i] & groupbit)
      buf[n] = x[i][1] + ((image[i] >> IMGBITS & IMGMASK) - IMGMAX) * yprd;
    else buf[n] = 0.0;
    n += nvalues;
  }
}
