warn_if_shadowing (tree new_decl)
{
  struct c_binding *b;


  if (!warn_shadow

      || DECL_IS_BUILTIN (new_decl)

      || DECL_FROM_INLINE (new_decl))
    return;


  for (b = I_SYMBOL_BINDING (DECL_NAME (new_decl)); b; b = b->shadowed)
    if (b->decl && b->decl != new_decl && !b->invisible)
      {
	tree old_decl = b->decl;

	if (old_decl == error_mark_node)
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows previous "
		     "non-variable", new_decl);
	    break;
	  }
	else if (TREE_CODE (old_decl) == PARM_DECL)
	  warning (OPT_Wshadow, "declaration of %q+D shadows a parameter",
		   new_decl);
	else if (DECL_FILE_SCOPE_P (old_decl))
	  warning (OPT_Wshadow, "declaration of %q+D shadows a global "
		   "declaration", new_decl);
	else if (TREE_CODE (old_decl) == FUNCTION_DECL
		 && DECL_BUILT_IN (old_decl))
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows "
		     "a built-in function", new_decl);
	    break;
	  }
	else
	  warning (OPT_Wshadow, "declaration of %q+D shadows a previous local",
		   new_decl);

	warning_at (DECL_SOURCE_LOCATION (old_decl), OPT_Wshadow,
		    "shadowed declaration is here");

	break;
      }
}
