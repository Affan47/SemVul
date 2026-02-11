hwloc_bitmap_snprintf(char * __hwloc_restrict buf, size_t buflen, const struct hwloc_bitmap_s * __hwloc_restrict set)
{
  ssize_t size = buflen;
  char *tmp = buf;
  int res, ret = 0;
  int needcomma = 0;
  int i;
  unsigned long accum = 0;
  int accumed = 0;
#if HWLOC_BITS_PER_LONG == HWLOC_BITMAP_SUBSTRING_SIZE
  const unsigned long accum_mask = ~0UL;
#else
  const unsigned long accum_mask = ((1UL << HWLOC_BITMAP_SUBSTRING_SIZE) - 1) << (HWLOC_BITS_PER_LONG - HWLOC_BITMAP_SUBSTRING_SIZE);
#endif

  HWLOC__BITMAP_CHECK(set);


  if (buflen > 0)
    tmp[0] = '\0';

  if (set->infinite) {
    res = hwloc_snprintf(tmp, size, "0xf...f");
    needcomma = 1;
    if (res < 0)
      return -1;
    ret += res;
    if (res >= size)
      res = size>0 ? size - 1 : 0;
    tmp += res;
    size -= res;

    if (set->ulongs_count == 1 && set->ulongs[0] == HWLOC_SUBBITMAP_FULL)
      return ret;
  }

  i=set->ulongs_count-1;
  while (i>=0 || accumed) {

    if (!accumed) {
      accum = set->ulongs[i--];
      accumed = HWLOC_BITS_PER_LONG;
    }

    if (accum & accum_mask) {

        res = hwloc_snprintf(tmp, size, needcomma ? ",0x" HWLOC_PRIxSUBBITMAP : "0x" HWLOC_PRIxSUBBITMAP,
		     (accum & accum_mask) >> (HWLOC_BITS_PER_LONG - HWLOC_BITMAP_SUBSTRING_SIZE));
      needcomma = 1;
    } else if (i == -1 && accumed == HWLOC_BITMAP_SUBSTRING_SIZE) {

      res = hwloc_snprintf(tmp, size, needcomma ? ",0x0" : "0x0");
    } else if (needcomma) {
      res = hwloc_snprintf(tmp, size, ",");
    } else {
      res = 0;
    }
    if (res < 0)
      return -1;
    ret += res;

#if HWLOC_BITS_PER_LONG == HWLOC_BITMAP_SUBSTRING_SIZE
    accum = 0;
    accumed = 0;
#else
    accum <<= HWLOC_BITMAP_SUBSTRING_SIZE;
    accumed -= HWLOC_BITMAP_SUBSTRING_SIZE;
#endif

    if (res >= size)
      res = size>0 ? size - 1 : 0;

    tmp += res;
    size -= res;
  }

  return ret;
}
