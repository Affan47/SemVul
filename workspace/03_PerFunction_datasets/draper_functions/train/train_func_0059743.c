decdir_to_dec(const char* decdir)
{
  char* p;
  const char* cp;
  double rval;
  int sign = 0;

  cp = &decdir[0];

  if ((*cp == 'W') || (*cp == 'S')) {
    sign = -1;
  } else if ((*cp == 'N') || (*cp == 'E')) {
    sign = 1;
  }

  rval = sign ? strtod(&decdir[1], &p) : strtod(&decdir[0], &p);

  if (sign == 0) {
    if ((*p == 'W') || (*p == 'S')) {
      sign = -1;
    } else if ((*p == 'N') || (*p == 'E')) {
      sign = 1;
    }
  }

  return(rval * sign);
}
