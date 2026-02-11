dec_to_intdeg(const double d)
{
  int ideg = 0;

  if (d >= 0) {
    ideg = (2147483647) - (d * 8388608);
  } else {
    ideg = (2147483647) - (fabs(d) * 8388608) + 1;
  }

  return(ideg);
}
