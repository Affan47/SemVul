split_constant_offset (tree exp, tree *var, tree *off)
{
  tree type = TREE_TYPE (exp), otype, op0, op1, e, o;
  enum tree_code code;

  *var = exp;
  *off = ssize_int (0);
  STRIP_NOPS (exp);

  if (automatically_generated_chrec_p (exp))
    return;

  otype = TREE_TYPE (exp);
  code = TREE_CODE (exp);
  extract_ops_from_tree (exp, &code, &op0, &op1);
  if (split_constant_offset_1 (otype, op0, code, op1, &e, &o))
    {
      *var = fold_convert (type, e);
      *off = o;
    }
}
