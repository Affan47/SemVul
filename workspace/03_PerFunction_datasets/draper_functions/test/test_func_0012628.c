mpc_set_str (mpc_t z, const char *str, int base, mpc_rnd_t rnd)
{
  char *p;
  int inex;

  inex = mpc_strtoc (z, str, &p, base, rnd);

  if (inex != -1){
     while (isspace ((unsigned char) (*p)))
        p++;
     if (*p == '\0')
        return inex;
  }

  mpfr_set_nan (mpc_realref (z));
  mpfr_set_nan (mpc_imagref (z));
  return -1;
}
