isoinfo (const char *path)
{
  int r;
  CLEANUP_FREE char *out = NULL, *err = NULL;
  CLEANUP_FREE_STRING_LIST char **lines = NULL;


  r = command (&out, &err, str_isoinfo, "--debug", "-d", "-i", path, NULL);
  if (r == -1) {
    reply_with_error ("%s", err);
    return NULL;
  }

  lines = split_lines (out);
  if (lines == NULL)
    return NULL;

  return parse_isoinfo (lines);
}
