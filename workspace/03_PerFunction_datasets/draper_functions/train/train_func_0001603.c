mode_check_assertion (NODE_T * p)
{
  SOID_T w, y;
  make_soid (&w, STRONG, MODE (BOOL), 0);
  mode_check_enclosed (SUB_NEXT (p), &w, &y);
  SORT (&y) = SORT (&w);
  if (!is_coercible_in_context (&y, &w, NO_DEFLEXING)) {
    cannot_coerce (NEXT (p), MOID (&y), MOID (&w), MEEK, NO_DEFLEXING, ENCLOSED_CLAUSE);
  }
}
