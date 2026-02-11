endian_read_float(const void* ptr, int read_le)
{
  float ret;
  char r[4];
  const void *p;
  int i;

  if (i_am_little_endian == read_le) {
    p = ptr;
  } else {
    for (i = 0; i < 4; i++) {
      r[i] = ((char*)ptr)[3-i];
    }
    p = r;
  }

  memcpy(&ret, p, 4);
  return ret;
}
