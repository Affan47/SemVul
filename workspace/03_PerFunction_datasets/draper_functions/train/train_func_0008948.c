_gcry_mpi_get_ui (gcry_mpi_t w, unsigned long *u)
{
  gcry_err_code_t err = GPG_ERR_NO_ERROR;
  unsigned long x = 0;

  if (w->nlimbs > 1)
    err = GPG_ERR_TOO_LARGE;
  else if (w->nlimbs == 1)
    x = w->d[0];
  else
    x = 0;

  if (! err)
    *u = x;

  return err;
}
