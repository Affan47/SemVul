hfsputil_perrorp(const char *path)
{
  const char *str = strerror(errno);

  if (!hfsp_error)
    fprintf(stderr, "%s: \"%s\": %c%s\n", argv0, path, *str, str + 1);
  else
    fprintf(stderr, "%s: \"%s\": %s (%s)\n", argv0, path, hfsp_error, str);
}
