bitmap_set_subtract (bitmap_set_t dest, bitmap_set_t orig)
{
  bitmap_set_t result = bitmap_set_new ();
  bitmap_iterator bi;
  unsigned int i;

  bitmap_and_compl (&result->expressions, &dest->expressions,
		    &orig->expressions);

  FOR_EACH_EXPR_ID_IN_SET (result, i, bi)
    {
      pre_expr expr = expression_for_id (i);
      unsigned int value_id = get_expr_value_id (expr);
      bitmap_set_bit (&result->values, value_id);
    }

  return result;
}
