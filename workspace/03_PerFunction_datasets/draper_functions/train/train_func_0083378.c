read_heapstate(dest_t *dest, glui32 chunklen, int portable,
  glui32 *sumlen, glui32 **summary)
{
  glui32 res, count, lx;
  glui32 *arr;

  *sumlen = 0;
  *summary = NULL;

  if (chunklen == 0)
    return 0;

  if (!portable) {
    count = chunklen / sizeof(glui32);

    arr = glulx_malloc(chunklen);
    if (!arr)
      return 1;

    res = read_buffer(dest, (void *)arr, chunklen);
    if (res)
      return res;

    *sumlen = count;
    *summary = arr;

    return 0;
  }

  count = chunklen / 4;

  arr = glulx_malloc(count * sizeof(glui32));
  if (!arr)
    return 1;

  for (lx=0; lx<count; lx++) {
    res = read_long(dest, arr+lx);
    if (res)
      return res;
  }

  *sumlen = count;
  *summary = arr;

  return 0;
}
