lto_symtab_merge_decls_2 (void **slot, bool diagnosed_p)
{
  lto_symtab_entry_t prevailing, e;
  VEC(tree, heap) *mismatches = NULL;
  unsigned i;
  tree decl;


  prevailing = (lto_symtab_entry_t) *slot;
  if (!prevailing->next)
    return;


  for (e = prevailing->next; e; e = e->next)
    {
      if (!lto_symtab_merge (prevailing, e)
	  && !diagnosed_p)
	VEC_safe_push (tree, heap, mismatches, e->decl);
    }
  if (VEC_empty (tree, mismatches))
    return;


  FOR_EACH_VEC_ELT (tree, mismatches, i, decl)
    {
      if (!types_compatible_p (TREE_TYPE (prevailing->decl), TREE_TYPE (decl)))
	diagnosed_p |= warning_at (DECL_SOURCE_LOCATION (decl), 0,
				   "type of %qD does not match original "
				   "declaration", decl);

      else if ((DECL_USER_ALIGN (prevailing->decl) && DECL_USER_ALIGN (decl))
	       && DECL_ALIGN (prevailing->decl) < DECL_ALIGN (decl))
	{
	  diagnosed_p |= warning_at (DECL_SOURCE_LOCATION (decl), 0,
				     "alignment of %qD is bigger than "
				     "original declaration", decl);
	}
    }
  if (diagnosed_p)
    inform (DECL_SOURCE_LOCATION (prevailing->decl),
	    "previously declared here");

  VEC_free (tree, heap, mismatches);
}
