is_coercible_stowed (MOID_T * p, MOID_T * q, int c, int deflex)
{
  if (c == STRONG) {
    if (q == MODE (VOID)) {
      return (A68_TRUE);
    } else if (IS (q, FLEX_SYMBOL)) {
      PACK_T *u = PACK (p);
      BOOL_T j = A68_TRUE;
      for (; u != NO_PACK && j; FORWARD (u)) {
        j &= is_coercible (MOID (u), SLICE (SUB (q)), c, deflex);
      }
      return (j);
    } else if (IS (q, ROW_SYMBOL)) {
      PACK_T *u = PACK (p);
      BOOL_T j = A68_TRUE;
      for (; u != NO_PACK && j; FORWARD (u)) {
        j &= is_coercible (MOID (u), SLICE (q), c, deflex);
      }
      return (j);
    } else if (IS (q, PROC_SYMBOL) || IS (q, STRUCT_SYMBOL)) {
      PACK_T *u = PACK (p), *v = PACK (q);
      if (DIM (p) != DIM (q)) {
        return (A68_FALSE);
      } else {
        BOOL_T j = A68_TRUE;
        while (u != NO_PACK && v != NO_PACK && j) {
          j &= is_coercible (MOID (u), MOID (v), c, deflex);
          FORWARD (u);
          FORWARD (v);
        }
        return (j);
      }
    } else {
      return (A68_FALSE);
    }
  } else {
    return (A68_FALSE);
  }
}
