pp_c_multiplicative_expression (c_pretty_printer *pp, tree e)
{
  enum tree_code code = TREE_CODE (e);
  switch (code)
    {
    case MULT_EXPR:
    case TRUNC_DIV_EXPR:
    case TRUNC_MOD_EXPR:
      pp_multiplicative_expression (pp, TREE_OPERAND (e, 0));
      pp_c_whitespace (pp);
      if (code == MULT_EXPR)
	pp_c_star (pp);
      else if (code == TRUNC_DIV_EXPR)
	pp_slash (pp);
      else
	pp_modulo (pp);
      pp_c_whitespace (pp);
      pp_c_cast_expression (pp, TREE_OPERAND (e, 1));
      break;

    default:
      pp_c_cast_expression (pp, e);
      break;
    }
}
