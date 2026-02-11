build_x_unary_op (enum tree_code code, tree xarg, tsubst_flags_t complain)
{
  tree orig_expr = xarg;
  tree exp;
  int ptrmem = 0;

  if (processing_template_decl)
    {
      if (type_dependent_expression_p (xarg))
	return build_min_nt (code, xarg, NULL_TREE);

      xarg = build_non_dependent_expr (xarg);
    }

  exp = NULL_TREE;


  if (code == ADDR_EXPR
      && TREE_CODE (xarg) != TEMPLATE_ID_EXPR
      && ((CLASS_TYPE_P (TREE_TYPE (xarg))
	   && !COMPLETE_TYPE_P (complete_type (TREE_TYPE (xarg))))
	  || (TREE_CODE (xarg) == OFFSET_REF)))
    ;
  else
    exp = build_new_op (code, LOOKUP_NORMAL, xarg, NULL_TREE, NULL_TREE,
			NULL, complain);
  if (!exp && code == ADDR_EXPR)
    {
      if (is_overloaded_fn (xarg))
	{
	  tree fn = get_first_fn (xarg);
	  if (DECL_CONSTRUCTOR_P (fn) || DECL_DESTRUCTOR_P (fn))
	    {
	      error (DECL_CONSTRUCTOR_P (fn)
                     ? G_("taking address of constructor %qE")
                     : G_("taking address of destructor %qE"),
                     xarg);
	      return error_mark_node;
	    }
	}


      if (!flag_ms_extensions && TREE_CODE (TREE_TYPE (xarg)) == METHOD_TYPE
	  && (TREE_CODE (xarg) != OFFSET_REF || !PTRMEM_OK_P (xarg)))
	{
	  if (TREE_CODE (xarg) != OFFSET_REF
	      || !TYPE_P (TREE_OPERAND (xarg, 0)))
	    {
              error ("invalid use of %qE to form a pointer-to-member-function",
                     xarg);
              if (TREE_CODE (xarg) != OFFSET_REF)
                inform (input_location, "  a qualified-id is required");
	      return error_mark_node;
	    }
	  else
	    {
	      error ("parentheses around %qE cannot be used to form a"
		     " pointer-to-member-function",
		     xarg);
	      PTRMEM_OK_P (xarg) = 1;
	    }
	}

      if (TREE_CODE (xarg) == OFFSET_REF)
	{
	  ptrmem = PTRMEM_OK_P (xarg);

	  if (!ptrmem && !flag_ms_extensions
	      && TREE_CODE (TREE_TYPE (TREE_OPERAND (xarg, 1))) == METHOD_TYPE)
	    {


	      xarg = build2 (OFFSET_REF, TREE_TYPE (xarg),
			     TREE_OPERAND (xarg, 0),
			     ovl_cons (TREE_OPERAND (xarg, 1), NULL_TREE));
	      PTRMEM_OK_P (xarg) = ptrmem;
	    }
	}

      exp = cp_build_addr_expr_strict (xarg, complain);
    }

  if (processing_template_decl && exp != error_mark_node)
    exp = build_min_non_dep (code, exp, orig_expr,
			     NULL_TREE);
  if (TREE_CODE (exp) == ADDR_EXPR)
    PTRMEM_OK_P (exp) = ptrmem;
  return exp;
}
