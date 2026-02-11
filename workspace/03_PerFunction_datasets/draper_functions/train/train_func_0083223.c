dump_scope_block (FILE *file, int indent, tree scope, int flags)
{
  tree var, t;
  unsigned int i;

  fprintf (file, "\n%*s{ Scope block #%i%s%s",indent, "" , BLOCK_NUMBER (scope),
  	   TREE_USED (scope) ? "" : " (unused)",
	   BLOCK_ABSTRACT (scope) ? " (abstract)": "");
  if (BLOCK_SOURCE_LOCATION (scope) != UNKNOWN_LOCATION)
    {
      expanded_location s = expand_location (BLOCK_SOURCE_LOCATION (scope));
      fprintf (file, " %s:%i", s.file, s.line);
    }
  if (BLOCK_ABSTRACT_ORIGIN (scope))
    {
      tree origin = block_ultimate_origin (scope);
      if (origin)
	{
	  fprintf (file, " Originating from :");
	  if (DECL_P (origin))
	    print_generic_decl (file, origin, flags);
	  else
	    fprintf (file, "#%i", BLOCK_NUMBER (origin));
	}
    }
  fprintf (file, " \n");
  for (var = BLOCK_VARS (scope); var; var = DECL_CHAIN (var))
    {
      bool used = false;

      if (var_ann (var))
	used = is_used_p (var);

      fprintf (file, "%*s", indent, "");
      print_generic_decl (file, var, flags);
      fprintf (file, "%s\n", used ? "" : " (unused)");
    }
  for (i = 0; i < BLOCK_NUM_NONLOCALIZED_VARS (scope); i++)
    {
      fprintf (file, "%*s",indent, "");
      print_generic_decl (file, BLOCK_NONLOCALIZED_VAR (scope, i),
      			  flags);
      fprintf (file, " (nonlocalized)\n");
    }
  for (t = BLOCK_SUBBLOCKS (scope); t ; t = BLOCK_CHAIN (t))
    dump_scope_block (file, indent + 2, t, flags);
  fprintf (file, "\n%*s}\n",indent, "");
}
