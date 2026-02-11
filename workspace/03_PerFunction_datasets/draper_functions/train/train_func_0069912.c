do_df (void)
{
  int r;
  char *out;
  CLEANUP_FREE char *err = NULL;

  NEED_ROOT (, return NULL);

  r = command (&out, &err, str_df, NULL);
  if (r == -1) {
    reply_with_error ("%s", err);
    free (out);
    return NULL;
  }

  return out;
}
