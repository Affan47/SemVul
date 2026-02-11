whereMax(double *buffer, int npix)
{

  double max    = buffer[0];
  int    maxpos = 0;
  int    i;


  for (i = 1; i < npix; i++) {
    if (buffer[i] > max) {
      max = buffer[i];
      maxpos = i;
    }
  }

  return maxpos;

}
