cmp16(const void *a, const void *b)
{
  register u_int16 *la, *lb;
  char *d;

  d = *(char**)a;
  la = (u_int16*)(d+sort_offset);

  d = *(char**)b;
  lb = (u_int16*)(d+sort_offset);

  if (*la < *lb)
    return -1;
  if (*la > *lb)
    return 1;
  return 0;

}
