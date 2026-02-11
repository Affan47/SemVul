error_callback (void *data, const char *msg, int errnum)
{
  struct print_data *pdata = (struct print_data *) data;

  if (pdata->state->filename != NULL)
    fprintf (stderr, "%s: ", pdata->state->filename);
  fprintf (stderr, "libbacktrace: %s", msg);
  if (errnum > 0)
    fprintf (stderr, ": %s", strerror (errnum));
  fputc ('\n', stderr);
}
