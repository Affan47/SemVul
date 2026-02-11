c_expand_return (retval)
     tree retval;
{
  tree valtype = TREE_TYPE (TREE_TYPE (current_function_decl));

  if (TREE_THIS_VOLATILE (current_function_decl))
    warning ("function declared `noreturn' has a `return' statement");

  if (!retval)
    {
      current_function_returns_null = 1;
      if ((warn_return_type || flag_isoc99)
	  && valtype != 0 && TREE_CODE (valtype) != VOID_TYPE)
	pedwarn_c99 ("`return' with no value, in function returning non-void");
    }
  else if (valtype == 0 || TREE_CODE (valtype) == VOID_TYPE)
    {
      current_function_returns_null = 1;
      if (pedantic || TREE_CODE (TREE_TYPE (retval)) != VOID_TYPE)
	pedwarn ("`return' with a value, in function returning void");
    }
  else
    {
      tree t = convert_for_assignment (valtype, retval, _("return"),
				       NULL_TREE, NULL_TREE, 0);
      tree res = DECL_RESULT (current_function_decl);
      tree inner;

      current_function_returns_value = 1;
      if (t == error_mark_node)
	return NULL_TREE;

      inner = t = convert (TREE_TYPE (res), t);


      while (1)
	{
	  switch (TREE_CODE (inner))
	    {
	    case NOP_EXPR:   case NON_LVALUE_EXPR:  case CONVERT_EXPR:
	    case PLUS_EXPR:
	      inner = TREE_OPERAND (inner, 0);
	      continue;

	    case MINUS_EXPR:


	      {
		tree op1 = TREE_OPERAND (inner, 1);

		while (! POINTER_TYPE_P (TREE_TYPE (op1))
		       && (TREE_CODE (op1) == NOP_EXPR
			   || TREE_CODE (op1) == NON_LVALUE_EXPR
			   || TREE_CODE (op1) == CONVERT_EXPR))
		  op1 = TREE_OPERAND (op1, 0);

		if (POINTER_TYPE_P (TREE_TYPE (op1)))
		  break;

		inner = TREE_OPERAND (inner, 0);
		continue;
	      }

	    case ADDR_EXPR:
	      inner = TREE_OPERAND (inner, 0);

	      while (TREE_CODE_CLASS (TREE_CODE (inner)) == 'r')
		inner = TREE_OPERAND (inner, 0);

	      if (TREE_CODE (inner) == VAR_DECL
		  && ! DECL_EXTERNAL (inner)
		  && ! TREE_STATIC (inner)
		  && DECL_CONTEXT (inner) == current_function_decl)
		warning ("function returns address of local variable");
	      break;

	    default:
	      break;
	    }

	  break;
	}

      retval = build (MODIFY_EXPR, TREE_TYPE (res), res, t);
    }

 return add_stmt (build_return_stmt (retval));
}
