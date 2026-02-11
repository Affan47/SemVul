maybe_warn_about_returning_address_of_local (tree retval)
{
  tree valtype = TREE_TYPE (DECL_RESULT (current_function_decl));
  tree whats_returned = retval;

  for (;;)
    {
      if (TREE_CODE (whats_returned) == COMPOUND_EXPR)
	whats_returned = TREE_OPERAND (whats_returned, 1);
      else if (CONVERT_EXPR_P (whats_returned)
	       || TREE_CODE (whats_returned) == NON_LVALUE_EXPR)
	whats_returned = TREE_OPERAND (whats_returned, 0);
      else
	break;
    }

  if (TREE_CODE (whats_returned) != ADDR_EXPR)
    return;
  whats_returned = TREE_OPERAND (whats_returned, 0);

  if (TREE_CODE (valtype) == REFERENCE_TYPE)
    {
      if (TREE_CODE (whats_returned) == AGGR_INIT_EXPR
	  || TREE_CODE (whats_returned) == TARGET_EXPR)
	{
	  warning (0, "returning reference to temporary");
	  return;
	}
      if (TREE_CODE (whats_returned) == VAR_DECL
	  && DECL_NAME (whats_returned)
	  && TEMP_NAME_P (DECL_NAME (whats_returned)))
	{
	  warning (0, "reference to non-lvalue returned");
	  return;
	}
    }

  while (TREE_CODE (whats_returned) == COMPONENT_REF
	 || TREE_CODE (whats_returned) == ARRAY_REF)
    whats_returned = TREE_OPERAND (whats_returned, 0);

  if (DECL_P (whats_returned)
      && DECL_NAME (whats_returned)
      && DECL_FUNCTION_SCOPE_P (whats_returned)
      && !(TREE_STATIC (whats_returned)
	   || TREE_PUBLIC (whats_returned)))
    {
      if (TREE_CODE (valtype) == REFERENCE_TYPE)
	warning (0, "reference to local variable %q+D returned",
		 whats_returned);
      else
	warning (0, "address of local variable %q+D returned",
		 whats_returned);
      return;
    }
}
