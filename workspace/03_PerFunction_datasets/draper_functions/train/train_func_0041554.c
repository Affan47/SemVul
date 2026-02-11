pp_c_initializer_list (c_pretty_printer *pp, tree e)
{
  tree type = TREE_TYPE (e);
  const enum tree_code code = TREE_CODE (type);

  if (TREE_CODE (e) == CONSTRUCTOR)
    {
      pp_c_constructor_elts (pp, CONSTRUCTOR_ELTS (e));
      return;
    }

  switch (code)
    {
    case RECORD_TYPE:
    case UNION_TYPE:
    case ARRAY_TYPE:
      {
	tree init = TREE_OPERAND (e, 0);
	for (; init != NULL_TREE; init = TREE_CHAIN (init))
	  {
	    if (code == RECORD_TYPE || code == UNION_TYPE)
	      {
		pp_c_dot (pp);
		pp_c_primary_expression (pp, TREE_PURPOSE (init));
	      }
	    else
	      {
		pp_c_left_bracket (pp);
		if (TREE_PURPOSE (init))
		  pp_c_constant (pp, TREE_PURPOSE (init));
		pp_c_right_bracket (pp);
	      }
	    pp_c_whitespace (pp);
	    pp_equal (pp);
	    pp_c_whitespace (pp);
	    pp_initializer (pp, TREE_VALUE (init));
	    if (TREE_CHAIN (init))
	      pp_separate_with (pp, ',');
	  }
      }
      return;

    case VECTOR_TYPE:
      if (TREE_CODE (e) == VECTOR_CST)
	pp_c_expression_list (pp, TREE_VECTOR_CST_ELTS (e));
      else
	break;
      return;

    case COMPLEX_TYPE:
      if (TREE_CODE (e) == COMPLEX_CST || TREE_CODE (e) == COMPLEX_EXPR)
	{
	  const bool cst = TREE_CODE (e) == COMPLEX_CST;
	  pp_expression (pp, cst ? TREE_REALPART (e) : TREE_OPERAND (e, 0));
	  pp_separate_with (pp, ',');
	  pp_expression (pp, cst ? TREE_IMAGPART (e) : TREE_OPERAND (e, 1));
	}
      else
	break;
      return;

    default:
      break;
    }

  pp_unsupported_tree (pp, type);
}
