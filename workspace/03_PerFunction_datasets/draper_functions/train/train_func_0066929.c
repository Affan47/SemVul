mode_check_unit_list_2 (NODE_T * p, SOID_T * x, SOID_T * y)
{
  SOID_T *top_sl = NO_SOID;
  if (MOID (x) != NO_MOID) {
    if (IS (MOID (x), FLEX_SYMBOL)) {
      SOID_T y2;
      make_soid (&y2, SORT (x), SLICE (SUB_MOID (x)), 0);
      mode_check_unit_list (&top_sl, SUB (p), &y2);
    } else if (IS (MOID (x), ROW_SYMBOL)) {
      SOID_T y2;
      make_soid (&y2, SORT (x), SLICE (MOID (x)), 0);
      mode_check_unit_list (&top_sl, SUB (p), &y2);
    } else if (IS (MOID (x), STRUCT_SYMBOL)) {
      PACK_T *y2 = PACK (MOID (x));
      mode_check_struct_display (&top_sl, SUB (p), &y2);
    } else {
      mode_check_unit_list (&top_sl, SUB (p), x);
    }
  } else {
    mode_check_unit_list (&top_sl, SUB (p), x);
  }
  make_soid (y, STRONG, pack_soids_in_moid (top_sl, STOWED_MODE), 0);
  free_soid_list (top_sl);
}
