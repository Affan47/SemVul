is_subset (MOID_T * p, MOID_T * q, int deflex)
{
  PACK_T *u = PACK (p);
  BOOL_T j = A68_TRUE;
  for (; u != NO_PACK && j; FORWARD (u)) {
    j = (BOOL_T) (j && is_moid_in_pack (MOID (u), PACK (q), deflex));
  }
  return (j);
}
