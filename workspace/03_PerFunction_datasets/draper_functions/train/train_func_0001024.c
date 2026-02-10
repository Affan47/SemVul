pack_iy(int n)
{
  tagint *image = atom->image;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  for (int i = 0; i < nlocal; i++) {
    if (mask[i] & groupbit) buf[n] = (image[i] >> IMGBITS & IMGMASK) - IMGMAX;
    else buf[n] = 0.0;
    n += nvalues;
  }
}
