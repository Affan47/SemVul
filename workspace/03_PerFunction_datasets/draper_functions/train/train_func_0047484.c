memory_usage()
{
  double bytes = 0.0;
  for (int m = 0; m < nvector; m++)
    bytes += atom->nmax*peratom[m]*sizeof(double);
  return bytes;
}
