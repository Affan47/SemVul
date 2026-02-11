dependent_clean (bitmap_set_t set1, bitmap_set_t set2, basic_block block)
{
  VEC (pre_expr, heap) *exprs = sorted_array_from_bitmap_set (set1);
  pre_expr expr;
  int i;

  FOR_EACH_VEC_ELT (pre_expr, exprs, i, expr)
    {
      if (!valid_in_sets (set1, set2, expr, block))
	bitmap_remove_from_set (set1, expr);
    }
  VEC_free (pre_expr, heap, exprs);
}
