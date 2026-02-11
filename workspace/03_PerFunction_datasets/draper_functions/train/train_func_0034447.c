read_file (const char *fname, size_t *r_length)
{
  FILE *fp;
  char *buf;
  size_t buflen;
  struct stat st;

  fp = fopen (fname, "rb");
  if (!fp)
    {
      fprintf (stderr, "%s:%d: can't open `%s': %s\n",
               __FILE__, __LINE__, fname, strerror (errno));
      exit (1);
    }

  if (fstat (fileno(fp), &st))
    {
      fprintf (stderr, "%s:%d: can't stat `%s': %s\n",
               __FILE__, __LINE__, fname, strerror (errno));
      exit (1);
    }

  buflen = st.st_size;
  buf = xmalloc (buflen+1);
  if (fread (buf, buflen, 1, fp) != 1)
    {
      fprintf (stderr, "%s:%d: error reading `%s': %s\n",
               __FILE__, __LINE__, fname, strerror (errno));
      exit (1);
    }
  fclose (fp);

  *r_length = buflen;
  return buf;
}
