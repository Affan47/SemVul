mode_check_cast (NODE_T * p, SOID_T * x, SOID_T * y)
{
  SOID_T w;
  mode_check_declarer (p);
  make_soid (&w, STRONG, MOID (p), 0);
  CAST (&w) = A68_TRUE;
  mode_check_enclosed (SUB_NEXT (p), &w, y);
  if (!is_coercible_in_context (y, &w, SAFE_DEFLEXING)) {
    cannot_coerce (NEXT (p), MOID (y), MOID (&w), STRONG, SAFE_DEFLEXING, ENCLOSED_CLAUSE);
  }
  make_soid (y, SORT (x), MOID (p), 0);
}
