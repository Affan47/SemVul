is_coercible_series (MOID_T * p, MOID_T * q, int c, int deflex)
{
  if (c != STRONG) {
    return (A68_FALSE);
  } else if (p == NO_MOID || q == NO_MOID) {
    return (A68_FALSE);
  } else if (IS (p, SERIES_MODE) && PACK (p) == NO_PACK) {
    return (A68_FALSE);
  } else if (IS (q, SERIES_MODE) && PACK (q) == NO_PACK) {
    return (A68_FALSE);
  } else if (PACK (p) == NO_PACK) {
    return (is_coercible (p, q, c, deflex));
  } else {
    PACK_T *u = PACK (p);
    BOOL_T j = A68_TRUE;
    for (; u != NO_PACK && j; FORWARD (u)) {
      if (MOID (u) != NO_MOID) {
        j &= is_coercible (MOID (u), q, c, deflex);
      }
    }
    return (j);
  }
}
