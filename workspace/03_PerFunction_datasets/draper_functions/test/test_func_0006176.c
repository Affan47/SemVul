open_nointr (const char *path, int flags, mode_t mode)
{
  int res;
  do
    res = open (path, flags, mode);
  while (G_UNLIKELY (res != 0 && errno == EINTR));
  return res;
}
