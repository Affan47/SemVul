is_packs_equivalent (PACK_T * s, PACK_T * t)
{
  for (; s != NO_PACK && t != NO_PACK; FORWARD (s), FORWARD (t)) {
    if (!is_modes_equivalent (MOID (s), MOID (t))) {
      return (A68_FALSE);
    }
    if (TEXT (s) != TEXT (t)) {
      return (A68_FALSE);
    }
  }
  return ((BOOL_T) (s == NO_PACK && t == NO_PACK));
}
