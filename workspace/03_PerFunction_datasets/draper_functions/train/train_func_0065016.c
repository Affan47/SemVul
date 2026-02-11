is_equal_modes (MOID_T * p, MOID_T * q, int deflex)
{
  if (deflex == FORCE_DEFLEXING) {
    return (DEFLEX (p) == DEFLEX (q));
  } else if (deflex == ALIAS_DEFLEXING) {
    if (IS (p, REF_SYMBOL) && IS (q, REF_SYMBOL)) {
      return (p == q || DEFLEX (p) == q);
    } else if (ISNT (p, REF_SYMBOL) && ISNT (q, REF_SYMBOL)) {
      return (DEFLEX (p) == DEFLEX (q));
    }
  } else if (deflex == SAFE_DEFLEXING) {
    if (ISNT (p, REF_SYMBOL) && ISNT (q, REF_SYMBOL)) {
      return (DEFLEX (p) == DEFLEX (q));
    }
  }
  return (p == q);
}
