phi_translate_set (bitmap_set_t dest, bitmap_set_t set, basic_block pred,
		   basic_block phiblock)
{
  VEC (pre_expr, heap) *exprs;
  pre_expr expr;
  int i;

  if (gimple_seq_empty_p (phi_nodes (phiblock)))
    {
      bitmap_set_copy (dest, set);
      return;
    }

  exprs = sorted_array_from_bitmap_set (set);
  FOR_EACH_VEC_ELT (pre_expr, exprs, i, expr)
    {
      pre_expr translated;
      translated = phi_translate (expr, set, NULL, pred, phiblock);
      if (!translated)
	continue;


      if (translated->kind == NAME)
	bitmap_value_replace_in_set (dest, translated);
      else
	bitmap_value_insert_into_set (dest, translated);
    }
  VEC_free (pre_expr, heap, exprs);
}
