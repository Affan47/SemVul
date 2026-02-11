do_equal (const char *file1, const char *file2)
{
  CLEANUP_FREE char *file1buf = NULL, *file2buf = NULL;
  CLEANUP_FREE char *err = NULL;
  int r;

  file1buf = sysroot_path (file1);
  if (file1buf == NULL) {
    reply_with_perror ("malloc");
    return -1;
  }

  file2buf = sysroot_path (file2);
  if (file2buf == NULL) {
    reply_with_perror ("malloc");
    return -1;
  }

  r = commandr (NULL, &err, str_cmp, "-s", file1buf, file2buf, NULL);
  if (r == -1 || r > 1) {
    reply_with_error ("%s", err);
    return -1;
  }

  return r == 0;
}
