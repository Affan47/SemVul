pp_cxx_assignment_operator (cxx_pretty_printer *pp, tree t)
{
  const char *op;

  switch (TREE_CODE (t))
    {
    case NOP_EXPR:
      op = "=";
      break;

    case PLUS_EXPR:
      op = "+=";
      break;

    case MINUS_EXPR:
      op = "-=";
      break;

    case TRUNC_DIV_EXPR:
      op = "/=";
      break;

    case TRUNC_MOD_EXPR:
      op = "%=";
      break;

    default:
      op = tree_code_name[TREE_CODE (t)];
      break;
    }

  pp_cxx_ws_string (pp, op);
}
