lam_ptmalloc2_sbrk(int inc)
{
  if (inc < 0) {
    long oldp = (long) sbrk(0);
    lam_handle_free((void*) (oldp + inc), -inc);
  }

  return sbrk(inc);
}
