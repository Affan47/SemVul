pp_c_constant (c_pretty_printer *pp, tree e)
{
  const enum tree_code code = TREE_CODE (e);

  switch (code)
    {
    case INTEGER_CST:
      {
	tree type = TREE_TYPE (e);
	if (type == boolean_type_node)
	  pp_c_bool_constant (pp, e);
	else if (type == char_type_node)
	  pp_c_character_constant (pp, e);
	else if (TREE_CODE (type) == ENUMERAL_TYPE
		 && pp_c_enumeration_constant (pp, e))
	  ;
	else
	  pp_c_integer_constant (pp, e);
      }
      break;

    case REAL_CST:
      pp_c_floating_constant (pp, e);
      break;

    case FIXED_CST:
      pp_c_fixed_constant (pp, e);
      break;

    case STRING_CST:
      pp_c_string_literal (pp, e);
      break;

    case COMPLEX_CST:


      pp_c_compound_literal (pp, e);
      break;

    default:
      pp_unsupported_tree (pp, e);
      break;
    }
}
