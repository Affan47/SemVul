renumber_moids (MOID_T * p, int n)
{
  if (p != NO_MOID) {
    NUMBER (p) = n;
    renumber_moids (NEXT (p), n + 1);
  }
}
