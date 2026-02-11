file_exists (const char *filename)
{
  struct stat  buf;
  int  res;
  res = stat (filename, &buf);
  if (! res)  return 1;
  if (res && errno != ENOENT) {
    fprintf (stderr, "error: cannot stat %s (%s)\n",
	     filename, strerror (errno));
    exit (1);
  }
  return 0;
}
