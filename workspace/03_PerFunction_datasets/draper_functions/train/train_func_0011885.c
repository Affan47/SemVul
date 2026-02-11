moid_needs_colouring (MOID_T * m)
{
  if (IS (m, REF_SYMBOL)) {
    return (A68_TRUE);
  } else if (IS (m, PROC_SYMBOL)) {
    return (A68_TRUE);
  } else if (IS (m, FLEX_SYMBOL) || IS (m, ROW_SYMBOL)) {
    return (A68_TRUE);
  } else if (IS (m, STRUCT_SYMBOL) || IS (m, UNION_SYMBOL)) {
    PACK_T *p = PACK (m);
    for (; p != NO_PACK; FORWARD (p)) {
      if (moid_needs_colouring (MOID (p))) {
        return (A68_TRUE);
      }
    }
    return (A68_FALSE);
  } else {
    return (A68_FALSE);
  }
}
