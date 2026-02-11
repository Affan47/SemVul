build_new (vec<tree, va_gc> **placement, tree type, tree nelts,
	   vec<tree, va_gc> **init, int use_global_new, tsubst_flags_t complain)
{
  tree rval;
  vec<tree, va_gc> *orig_placement = NULL;
  tree orig_nelts = NULL_TREE;
  vec<tree, va_gc> *orig_init = NULL;

  if (type == error_mark_node)
    return error_mark_node;

  if (nelts == NULL_TREE && vec_safe_length (*init) == 1

      && (!processing_template_decl || at_function_scope_p ()))
    {
      tree auto_node = type_uses_auto (type);
      if (auto_node)
	{
	  tree d_init = (**init)[0];
	  d_init = resolve_nondeduced_context (d_init);
	  type = do_auto_deduction (type, d_init, auto_node);
	}
    }

  if (processing_template_decl)
    {
      if (dependent_type_p (type)
	  || any_type_dependent_arguments_p (*placement)
	  || (nelts && type_dependent_expression_p (nelts))
	  || (nelts && *init)
	  || any_type_dependent_arguments_p (*init))
	return build_raw_new_expr (*placement, type, nelts, *init,
				   use_global_new);

      orig_placement = make_tree_vector_copy (*placement);
      orig_nelts = nelts;
      if (*init)
	orig_init = make_tree_vector_copy (*init);

      make_args_non_dependent (*placement);
      if (nelts)
	nelts = build_non_dependent_expr (nelts);
      make_args_non_dependent (*init);
    }

  if (nelts)
    {
      if (!build_expr_type_conversion (WANT_INT | WANT_ENUM, nelts, false))
        {
          if (complain & tf_error)
            permerror (input_location, "size in array new must have integral type");
          else
            return error_mark_node;
        }
      nelts = mark_rvalue_use (nelts);
      nelts = cp_save_expr (cp_convert (sizetype, nelts, complain));
    }


  if (TREE_CODE (type) == REFERENCE_TYPE)
    {
      if (complain & tf_error)
        error ("new cannot be applied to a reference type");
      else
        return error_mark_node;
      type = TREE_TYPE (type);
    }

  if (TREE_CODE (type) == FUNCTION_TYPE)
    {
      if (complain & tf_error)
        error ("new cannot be applied to a function type");
      return error_mark_node;
    }


  if (!complete_type_or_maybe_complain (type, NULL_TREE, complain))
    return error_mark_node;

  rval = build_new_1 (placement, type, nelts, init, use_global_new, complain);
  if (rval == error_mark_node)
    return error_mark_node;

  if (processing_template_decl)
    {
      tree ret = build_raw_new_expr (orig_placement, type, orig_nelts,
				     orig_init, use_global_new);
      release_tree_vector (orig_placement);
      release_tree_vector (orig_init);
      return ret;
    }


  rval = build1 (NOP_EXPR, TREE_TYPE (rval), rval);
  TREE_NO_WARNING (rval) = 1;

  return rval;
}
