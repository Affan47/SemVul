pack_zu(int n)
{
  double **x = atom->x;
  tagint *image = atom->image;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  double zprd = domain->zprd;

  for (int i = 0; i < nlocal; i++) {
    if (mask[i] & groupbit) {
      vbuf[n] = x[i][2] + ((image[i] >> IMG2BITS) - IMGMAX) * zprd;
      if (comflag) vbuf[n] -= cm[2];
    } else vbuf[n] = 0.0;
    n += nvalues;
  }
}
