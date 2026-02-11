deproc_completely (MOID_T * p)
{
  while (IS (p, PROC_SYMBOL) && PACK (p) == NO_PACK) {
    p = depref_once (p);
  }
  return (p);
}
