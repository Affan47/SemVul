SimpleVFilter16(uint8_t* p, int stride, int thresh) {
  int i;
  const int thresh2 = 2 * thresh + 1;
  for (i = 0; i < 16; ++i) {
    if (needs_filter(p + i, stride, thresh2)) {
      do_filter2(p + i, stride);
    }
  }
}
