tree_int_cst_min_precision (tree value, bool unsignedp)
{
  int log;


  if (tree_int_cst_sgn (value) < 0)
    value = fold_build1 (BIT_NOT_EXPR, TREE_TYPE (value), value);


  if (integer_zerop (value))
    log = 0;
  else
    log = tree_floor_log2 (value);

  return log + 1 + !unsignedp;
}
