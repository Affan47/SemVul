build_call_array_loc (location_t loc, tree return_type, tree fn,
		      int nargs, const tree *args)
{
  tree t;
  int i;

  t = build_call_1 (return_type, fn, nargs);
  for (i = 0; i < nargs; i++)
    CALL_EXPR_ARG (t, i) = args[i];
  process_call_operands (t);
  SET_EXPR_LOCATION (t, loc);
  return t;
}
