ppdb_decode_coord(const char *str)
{
  double val;
  int deg;
  char dir;

  if (*str < 'A') {
    CHECK_INP(1, sscanf(str,"%lf", &val), "decode_coord(1) DD.dddd", str);
    return val;
  } else {
    char *tmp;

    if (*str == 'O') {
      german_release = 1;
    }

    tmp = strchr(str, ' ');
    if ((tmp) && (tmp - str < 5)) {
      CHECK_INP(3, sscanf(str,"%c%d %lf", &dir, &deg, &val), "decode_coord(2) DD MM.mmm", str);
      val = deg + (val / 60.0);
    } else {
      CHECK_INP(2, sscanf(str,"%c%lf", &dir, &val), "decode_coord(3) DD.dddd", str);
    }
    if ((dir == 'S') || (dir == 'W')) {
      val = -val;
    }
  }
  return val;
}
