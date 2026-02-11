dump_template_parameter (tree parm, int flags)
{
  tree p = TREE_VALUE (parm);
  tree a = TREE_PURPOSE (parm);

  if (TREE_CODE (p) == TYPE_DECL)
    {
      if (flags & TFF_DECL_SPECIFIERS)
        {
          pp_identifier (cxx_pp, "class");
          if (DECL_NAME (p))
            {
              pp_space (cxx_pp);
              pp_tree_identifier (cxx_pp, DECL_NAME (p));
            }
        }
      else if (DECL_NAME (p))
        pp_tree_identifier (cxx_pp, DECL_NAME (p));
      else
        pp_cxx_canonical_template_parameter (cxx_pp, TREE_TYPE (p));
    }
  else
    dump_decl (p, flags | TFF_DECL_SPECIFIERS);

  if ((flags & TFF_FUNCTION_DEFAULT_ARGUMENTS) && a != NULL_TREE)
    {
      pp_string (cxx_pp, " = ");
      if (TREE_CODE (p) == TYPE_DECL || TREE_CODE (p) == TEMPLATE_DECL)
        dump_type (a, flags & ~TFF_CHASE_TYPEDEF);
      else
        dump_expr (a, flags | TFF_EXPR_IN_PARENS);
    }
}
