is_transparent_argb_area(const uint32_t* ptr, int stride, int size) {
  int y, x;
  for (y = 0; y < size; ++y) {
    for (x = 0; x < size; ++x) {
      if (ptr[x] & 0xff000000u) {
        return 0;
      }
    }
    ptr += stride;
  }
  return 1;
}
