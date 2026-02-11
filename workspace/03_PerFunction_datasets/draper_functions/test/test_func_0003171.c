hwloc_nolibxml_export_diff_buffer(hwloc_topology_diff_t diff, const char *refname, char **bufferp, int *buflenp)
{
  char *buffer;
  size_t bufferlen, res;

  bufferlen = 16384;
  buffer = malloc(bufferlen);
  res = hwloc___nolibxml_prepare_export_diff(diff, refname, buffer, bufferlen);

  if (res > bufferlen) {
    buffer = realloc(buffer, res);
    hwloc___nolibxml_prepare_export_diff(diff, refname, buffer, res);
  }

  *bufferp = buffer;
  *buflenp = res;
  return 0;
}
