dump_simple_decl (tree t, tree type, int flags)
{
  if (flags & TFF_DECL_SPECIFIERS)
    {
      if (TREE_CODE (t) == VAR_DECL
	  && DECL_DECLARED_CONSTEXPR_P (t))
	pp_cxx_ws_string (cxx_pp, "constexpr");
      dump_type_prefix (type, flags & ~TFF_UNQUALIFIED_NAME);
      pp_maybe_space (cxx_pp);
    }
  if (! (flags & TFF_UNQUALIFIED_NAME)
      && TREE_CODE (t) != PARM_DECL
      && (!DECL_INITIAL (t)
	  || TREE_CODE (DECL_INITIAL (t)) != TEMPLATE_PARM_INDEX))
    dump_scope (CP_DECL_CONTEXT (t), flags);
  flags &= ~TFF_UNQUALIFIED_NAME;
  if ((flags & TFF_DECL_SPECIFIERS)
      && DECL_TEMPLATE_PARM_P (t)
      && TEMPLATE_PARM_PARAMETER_PACK (DECL_INITIAL (t)))
    pp_string (cxx_pp, "...");
  if (DECL_NAME (t))
    dump_decl (DECL_NAME (t), flags);
  else
    pp_string (cxx_pp, M_("<anonymous>"));
  if (flags & TFF_DECL_SPECIFIERS)
    dump_type_suffix (type, flags);
}
