pp_c_literal (ppi, e)
     c_pretty_printer ppi;
     tree e;
{
  switch (TREE_CODE (e))
    {
    case INTEGER_CST:
      pp_c_integer_literal (ppi, e);
      break;

    case REAL_CST:
      pp_c_real_literal (ppi, e);
      break;

    case STRING_CST:
      pp_c_string_literal (ppi, e);
      break;

    default:
      pp_unsupported_tree (ppi, e);
      break;
    }
}
