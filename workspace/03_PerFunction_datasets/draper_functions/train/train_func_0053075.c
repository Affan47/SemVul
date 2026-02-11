ipa_discover_readonly_nonaddressable_vars (void)
{
  struct varpool_node *vnode;
  if (dump_file)
    fprintf (dump_file, "Clearing variable flags:");
  FOR_EACH_VARIABLE (vnode)
    if (vnode->finalized && varpool_all_refs_explicit_p (vnode)
	&& (TREE_ADDRESSABLE (vnode->symbol.decl)
	    || !TREE_READONLY (vnode->symbol.decl)))
      {
	bool written = false;
	bool address_taken = false;
	int i;
        struct ipa_ref *ref;
        for (i = 0; ipa_ref_list_referring_iterate (&vnode->symbol.ref_list,
						   i, ref)
		    && (!written || !address_taken); i++)
	  switch (ref->use)
	    {
	    case IPA_REF_ADDR:
	      address_taken = true;
	      break;
	    case IPA_REF_LOAD:
	      break;
	    case IPA_REF_STORE:
	      written = true;
	      break;
	    }
	if (TREE_ADDRESSABLE (vnode->symbol.decl) && !address_taken)
	  {
	    if (dump_file)
	      fprintf (dump_file, " %s (addressable)", varpool_node_name (vnode));
	    TREE_ADDRESSABLE (vnode->symbol.decl) = 0;
	  }
	if (!TREE_READONLY (vnode->symbol.decl) && !address_taken && !written


	    && DECL_SECTION_NAME (vnode->symbol.decl) == NULL)
	  {
	    if (dump_file)
	      fprintf (dump_file, " %s (read-only)", varpool_node_name (vnode));
	    TREE_READONLY (vnode->symbol.decl) = 1;
	  }
      }
  if (dump_file)
    fprintf (dump_file, "\n");
}
