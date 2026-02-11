is_nonproc (MOID_T * p)
{
  if (IS (p, PROC_SYMBOL) && PACK (p) == NO_PACK) {
    return (A68_FALSE);
  } else if (IS (p, REF_SYMBOL)) {
    return (is_nonproc (SUB (p)));
  } else {
    return (A68_TRUE);
  }
}
