pp_cxx_offsetof_expression_1 (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case ARROW_EXPR:
      if (TREE_CODE (TREE_OPERAND (t, 0)) == STATIC_CAST_EXPR
	  && POINTER_TYPE_P (TREE_TYPE (TREE_OPERAND (t, 0))))
	{
	  pp_cxx_type_id (pp, TREE_TYPE (TREE_TYPE (TREE_OPERAND (t, 0))));
	  pp_cxx_separate_with (pp, ',');
	  return true;
	}
      return false;
    case COMPONENT_REF:
      if (!pp_cxx_offsetof_expression_1 (pp, TREE_OPERAND (t, 0)))
	return false;
      if (TREE_CODE (TREE_OPERAND (t, 0)) != ARROW_EXPR)
	pp_cxx_dot (pp);
      pp_cxx_expression (pp, TREE_OPERAND (t, 1));
      return true;
    case ARRAY_REF:
      if (!pp_cxx_offsetof_expression_1 (pp, TREE_OPERAND (t, 0)))
	return false;
      pp_left_bracket (pp);
      pp_cxx_expression (pp, TREE_OPERAND (t, 1));
      pp_right_bracket (pp);
      return true;
    default:
      return false;
    }
}
