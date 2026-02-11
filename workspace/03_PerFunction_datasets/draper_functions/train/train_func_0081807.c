remove(int i) {
  arrayLocker();
  if (i < 0 || i >= length) {
#ifdef DEBUG_MEM
    abort();
#else
    return;
#endif
  }
  --length;
  memmove( elems + i, elems + i + 1, sizeof(elems[0]) * (length - i) );
}
