dcompare(const double *pos1, const double *pos2)
{
  if (*pos1 < *pos2) {
    return(-1);
  }
  else if (*pos1 > *pos2) {
    return(1);
  }
  else {
    return(0);
  }
}
