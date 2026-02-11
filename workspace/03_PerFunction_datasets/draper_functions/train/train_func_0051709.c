check_for_out_of_scope_variable (tree decl)
{
  tree shadowed;


  if (!(TREE_CODE (decl) == VAR_DECL && DECL_DEAD_FOR_LOCAL (decl)))
    return decl;

  shadowed = DECL_SHADOWED_FOR_VAR (decl);
  while (shadowed != NULL_TREE && TREE_CODE (shadowed) == VAR_DECL
	 && DECL_DEAD_FOR_LOCAL (shadowed))
    shadowed = DECL_SHADOWED_FOR_VAR (shadowed);
  if (!shadowed)
    shadowed = IDENTIFIER_NAMESPACE_VALUE (DECL_NAME (decl));
  if (shadowed)
    {
      if (!DECL_ERROR_REPORTED (decl))
	{
	  warning ("name lookup of `%D' changed",
		      DECL_NAME (decl));
	  cp_warning_at ("  matches this `%D' under ISO standard rules",
			 shadowed);
	  cp_warning_at ("  matches this `%D' under old rules", decl);
	  DECL_ERROR_REPORTED (decl) = 1;
	}
      return shadowed;
    }


  if (DECL_ERROR_REPORTED (decl))
    return decl;

  DECL_ERROR_REPORTED (decl) = 1;

  if (TREE_TYPE (decl) == error_mark_node)
    return decl;

  if (TYPE_HAS_NONTRIVIAL_DESTRUCTOR (TREE_TYPE (decl)))
    {
      error ("name lookup of `%D' changed for new ISO `for' scoping",
	     DECL_NAME (decl));
      cp_error_at ("  cannot use obsolete binding at `%D' because it has a destructor", decl);
      return error_mark_node;
    }
  else
    {
      pedwarn ("name lookup of `%D' changed for new ISO `for' scoping",
	       DECL_NAME (decl));
      cp_pedwarn_at ("  using obsolete binding at `%D'", decl);
    }

  return decl;
}
