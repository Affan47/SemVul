pp_c_assignment_expression (c_pretty_printer *pp, tree e)
{
  if (TREE_CODE (e) == MODIFY_EXPR
      || TREE_CODE (e) == INIT_EXPR)
    {
      pp_c_unary_expression (pp, TREE_OPERAND (e, 0));
      pp_c_whitespace (pp);
      pp_equal (pp);
      pp_space (pp);
      pp_c_expression (pp, TREE_OPERAND (e, 1));
    }
  else
    pp_c_conditional_expression (pp, e);
}
