read_floats(FILE *f) {
  int n;
  double *fp;

  if ((bytein(f) != '#') || (bytein(f) != '@')
      || (bytein(f) != fasl_symbol) || (longin(f) != 4)
      || (bytein(f) != '5') || (bytein(f) != '.') || (bytein(f) != '0')
      || (bytein(f) != 'g') || (bytein(f) != fasl_pair)) {
    fprintf(stderr, "bad fasl file\n");
    exit(2);
  }

  nfloats = longin(f);
  floats = (double *)malloc(nfloats*sizeof(double));
  for (n = nfloats, fp = floats; n > 0; n--) {
    char s;
    int e, h, l;

    if (bytein(f) != fasl_flonum) {
      fprintf(stderr, "non-flonum in list\n");
      exit(3);
    }
    s = bytein(f);
    e = longin(f);
    h = longin(f);
    l = longin(f);
    *fp++ = build_float(s, e, h, l);
  }

  if ((bytein(f) != fasl_immediate) || (longin(f) != 38)
      || (bytein(f) != EOF)) {
    fprintf(stderr, "improper list\n");
    exit(4);
  }
}
