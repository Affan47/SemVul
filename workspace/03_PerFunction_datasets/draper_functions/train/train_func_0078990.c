get_val(char *val) {
  long ret;
  if (!(sscanf(val, "%ld", &ret) == 1)) {
    fprintf(stderr, _("%s: bad value\n"), progname);
    exit(3);
  }
  return ret;
}
