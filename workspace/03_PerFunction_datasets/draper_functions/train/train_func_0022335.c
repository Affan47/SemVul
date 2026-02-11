pp_c_parameter_type_list (c_pretty_printer *pp, tree t)
{
  bool want_parm_decl = DECL_P (t) && !(pp->flags & pp_c_flag_abstract);
  tree parms = want_parm_decl ? DECL_ARGUMENTS (t) :  TYPE_ARG_TYPES (t);
  pp_c_left_paren (pp);
  if (parms == void_list_node)
    pp_c_ws_string (pp, "void");
  else
    {
      bool first = true;
      for ( ; parms && parms != void_list_node; parms = TREE_CHAIN (parms))
	{
	  if (!first)
	    pp_separate_with (pp, ',');
	  first = false;
	  pp_declaration_specifiers
	    (pp, want_parm_decl ? parms : TREE_VALUE (parms));
	  if (want_parm_decl)
	    pp_declarator (pp, parms);
	  else
	    pp_abstract_declarator (pp, TREE_VALUE (parms));
	}
    }
  pp_c_right_paren (pp);
}
