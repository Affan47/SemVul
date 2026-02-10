build_x_arrow (location_t loc, tree expr, tsubst_flags_t complain)
{
  tree orig_expr = expr;
  tree type = TREE_TYPE (expr);
  tree last_rval = NULL_TREE;
  vec<tree, va_gc> *types_memoized = NULL;

  if (type == error_mark_node)
    return error_mark_node;

  if (processing_template_decl)
    {
      if (type_dependent_expression_p (expr))
	return build_min_nt_loc (loc, ARROW_EXPR, expr);
      expr = build_non_dependent_expr (expr);
    }

  if (MAYBE_CLASS_TYPE_P (type))
    {
      struct tinst_level *actual_inst = current_instantiation ();
      tree fn = NULL;

      while ((expr = build_new_op (loc, COMPONENT_REF,
				   LOOKUP_NORMAL, expr, NULL_TREE, NULL_TREE,
				   &fn, complain)))
	{
	  if (expr == error_mark_node)
	    return error_mark_node;

	  if (fn && DECL_USE_TEMPLATE (fn))
	    push_tinst_level (fn);
	  fn = NULL;

	  if (vec_member (TREE_TYPE (expr), types_memoized))
	    {
	      if (complain & tf_error)
		error ("circular pointer delegation detected");
	      return error_mark_node;
	    }

	  vec_safe_push (types_memoized, TREE_TYPE (expr));
	  last_rval = expr;
	}

      while (current_instantiation () != actual_inst)
	pop_tinst_level ();

      if (last_rval == NULL_TREE)
	{
	  if (complain & tf_error)
	    error ("base operand of %<->%> has non-pointer type %qT", type);
	  return error_mark_node;
	}

      if (TREE_CODE (TREE_TYPE (last_rval)) == REFERENCE_TYPE)
	last_rval = convert_from_reference (last_rval);
    }
  else
    last_rval = decay_conversion (expr, complain);

  if (TREE_CODE (TREE_TYPE (last_rval)) == POINTER_TYPE)
    {
      if (processing_template_decl)
	{
	  expr = build_min (ARROW_EXPR, TREE_TYPE (TREE_TYPE (last_rval)),
			    orig_expr);
	  TREE_SIDE_EFFECTS (expr) = TREE_SIDE_EFFECTS (last_rval);
	  return expr;
	}

      return cp_build_indirect_ref (last_rval, RO_NULL, complain);
    }

  if (complain & tf_error)
    {
      if (types_memoized)
	error ("result of %<operator->()%> yields non-pointer result");
      else
	error ("base operand of %<->%> is not a pointer");
    }
  return error_mark_node;
}
