build_static_cast (tree type, tree expr, tsubst_flags_t complain)
{
  tree result;
  bool valid_p;

  if (type == error_mark_node || expr == error_mark_node)
    return error_mark_node;

  if (processing_template_decl)
    {
      expr = build_min (STATIC_CAST_EXPR, type, expr);

      TREE_SIDE_EFFECTS (expr) = 1;
      return convert_from_reference (expr);
    }


  if (TREE_CODE (type) != REFERENCE_TYPE
      && TREE_CODE (expr) == NOP_EXPR
      && TREE_TYPE (expr) == TREE_TYPE (TREE_OPERAND (expr, 0)))
    expr = TREE_OPERAND (expr, 0);

  result = build_static_cast_1 (type, expr, false, &valid_p,
                                complain);
  if (valid_p)
    {
      if (result != error_mark_node)
	maybe_warn_about_useless_cast (type, expr, complain);
      return result;
    }

  if (complain & tf_error)
    error ("invalid static_cast from type %qT to type %qT",
           TREE_TYPE (expr), type);
  return error_mark_node;
}
