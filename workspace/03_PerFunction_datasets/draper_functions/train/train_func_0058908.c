hwloc_read_unit32be(const char *p, const char *p1, uint32_t *buf, int root_fd)
{
  size_t cb = 0;
  uint32_t *tmp = hwloc_read_raw(p, p1, &cb, root_fd);
  if (sizeof(*buf) != cb) {
    errno = EINVAL;
    free(tmp);
    return -1;
  }
  *buf = htonl(*tmp);
  free(tmp);
  return sizeof(*buf);
}
