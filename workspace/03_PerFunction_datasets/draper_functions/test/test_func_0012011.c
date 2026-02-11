dump_parameters (tree parmtypes, int flags)
{
  int first;

  pp_left_paren (cxx_pp);

  for (first = 1; parmtypes != void_list_node;
       parmtypes = TREE_CHAIN (parmtypes))
    {
      if (!first)
        pp_separate_with_comma (cxx_pp);
      first = 0;
      if (!parmtypes)
        {
          pp_identifier (cxx_pp, "...");
          break;
        }
      dump_type (TREE_VALUE (parmtypes), flags);

      if ((flags & TFF_FUNCTION_DEFAULT_ARGUMENTS) && TREE_PURPOSE (parmtypes))
        {
          pp_string (cxx_pp, " = ");
          dump_expr (TREE_PURPOSE (parmtypes), flags | TFF_EXPR_IN_PARENS);
        }
    }

  pp_right_paren (cxx_pp);
}
