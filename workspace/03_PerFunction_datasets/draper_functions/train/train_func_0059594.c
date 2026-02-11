read_sexp_from_file (const char *fname)
{
  gcry_error_t err;
  FILE *fp;
  char *buffer;
  size_t buflen;
  gcry_sexp_t sexp;

  fp = fopen (fname, "rb");
  if (!fp)
    die ("can't open `%s': %s\n", fname, strerror (errno));
  buffer = read_file (fp, 0, &buflen);
  if (!buffer)
    die ("error reading `%s'\n", fname);
  fclose (fp);
  if (!buflen)
    die ("error: file `%s' is empty\n", fname);

  err = gcry_sexp_create (&sexp, buffer, buflen, 1, gcry_free);
  if (err)
    die ("error parsing `%s': %s\n", fname, gpg_strerror (err));

  return sexp;
}
