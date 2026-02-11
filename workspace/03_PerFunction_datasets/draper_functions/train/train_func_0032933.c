cxx_alignof_expr (tree e, tsubst_flags_t complain)
{
  tree t;

  if (e == error_mark_node)
    return error_mark_node;

  if (processing_template_decl)
    {
      e = build_min (ALIGNOF_EXPR, size_type_node, e);
      TREE_SIDE_EFFECTS (e) = 0;
      TREE_READONLY (e) = 1;

      return e;
    }

  e = mark_type_use (e);

  if (TREE_CODE (e) == VAR_DECL)
    t = size_int (DECL_ALIGN_UNIT (e));
  else if (TREE_CODE (e) == COMPONENT_REF
	   && TREE_CODE (TREE_OPERAND (e, 1)) == FIELD_DECL
	   && DECL_C_BIT_FIELD (TREE_OPERAND (e, 1)))
    {
      if (complain & tf_error)
        error ("invalid application of %<__alignof%> to a bit-field");
      else
        return error_mark_node;
      t = size_one_node;
    }
  else if (TREE_CODE (e) == COMPONENT_REF
	   && TREE_CODE (TREE_OPERAND (e, 1)) == FIELD_DECL)
    t = size_int (DECL_ALIGN_UNIT (TREE_OPERAND (e, 1)));
  else if (is_overloaded_fn (e))
    {
      if (complain & tf_error)
        permerror (input_location, "ISO C++ forbids applying %<__alignof%> to an expression of "
                   "function type");
      else
        return error_mark_node;
      if (TREE_CODE (e) == FUNCTION_DECL)
	t = size_int (DECL_ALIGN_UNIT (e));
      else
	t = size_one_node;
    }
  else if (type_unknown_p (e))
    {
      if (complain & tf_error)
        cxx_incomplete_type_error (e, TREE_TYPE (e));
      else
        return error_mark_node;
      t = size_one_node;
    }
  else
    return cxx_sizeof_or_alignof_type (TREE_TYPE (e), ALIGNOF_EXPR,
                                       complain & tf_error);

  return fold_convert (size_type_node, t);
}
