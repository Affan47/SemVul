fold_builtin_fabs (location_t loc, tree arg, tree type)
{
  if (!validate_arg (arg, REAL_TYPE))
    return NULL_TREE;

  arg = fold_convert_loc (loc, type, arg);
  if (TREE_CODE (arg) == REAL_CST)
    return fold_abs_const (arg, type);
  return fold_build1_loc (loc, ABS_EXPR, type, arg);
}
