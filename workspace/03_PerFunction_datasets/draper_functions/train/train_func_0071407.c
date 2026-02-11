allocate(size_t n) {
  lock();
  void *retVal;
  if(n <= lvl1::N) retVal = lvl1::allocate(); else
  if(n <= lvl2::N) retVal = lvl2::allocate(); else
  if(n <= lvl3::N) retVal = lvl3::allocate(); else
  if(n <= lvl4::N) retVal = lvl4::allocate(); else
  retVal = _alloc_raw(n);
  unlock();
  return retVal;
}
