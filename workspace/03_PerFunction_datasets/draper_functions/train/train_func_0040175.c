cgraph_analyze_function (struct cgraph_node *node)
{
  tree save = current_function_decl;
  tree decl = node->decl;

  if (node->alias && node->thunk.alias)
    {
      struct cgraph_node *tgt = cgraph_get_node (node->thunk.alias);
      struct cgraph_node *n;

      for (n = tgt; n && n->alias;
	   n = n->analyzed ? cgraph_alias_aliased_node (n) : NULL)
	if (n == node)
	  {
	    error ("function %q+D part of alias cycle", node->decl);
	    node->alias = false;
	    return;
	  }
      if (!VEC_length (ipa_ref_t, node->ref_list.references))
        ipa_record_reference (node, NULL, tgt, NULL, IPA_REF_ALIAS, NULL);
      if (node->same_body_alias)
	{
	  DECL_VIRTUAL_P (node->decl) = DECL_VIRTUAL_P (node->thunk.alias);
	  DECL_DECLARED_INLINE_P (node->decl)
	     = DECL_DECLARED_INLINE_P (node->thunk.alias);
	  DECL_DISREGARD_INLINE_LIMITS (node->decl)
	     = DECL_DISREGARD_INLINE_LIMITS (node->thunk.alias);
	}


      if (TREE_PUBLIC (node->decl) && node->same_body_alias)
	{
          DECL_EXTERNAL (node->decl) = DECL_EXTERNAL (node->thunk.alias);
	  if (DECL_ONE_ONLY (node->thunk.alias))
	    {
	      DECL_COMDAT (node->decl) = DECL_COMDAT (node->thunk.alias);
	      DECL_COMDAT_GROUP (node->decl) = DECL_COMDAT_GROUP (node->thunk.alias);
	      if (DECL_ONE_ONLY (node->thunk.alias) && !node->same_comdat_group)
		{
		  struct cgraph_node *tgt = cgraph_get_node (node->thunk.alias);
		  node->same_comdat_group = tgt;
		  if (!tgt->same_comdat_group)
		    tgt->same_comdat_group = node;
		  else
		    {
		      struct cgraph_node *n;
		      for (n = tgt->same_comdat_group;
			   n->same_comdat_group != tgt;
			   n = n->same_comdat_group)
			;
		      n->same_comdat_group = node;
		    }
		}
	    }
	}
      cgraph_mark_reachable_node (cgraph_alias_aliased_node (node));
      if (node->address_taken)
	cgraph_mark_address_taken_node (cgraph_alias_aliased_node (node));
      if (cgraph_decide_is_function_needed (node, node->decl))
	cgraph_mark_needed_node (node);
    }
  else if (node->thunk.thunk_p)
    {
      cgraph_create_edge (node, cgraph_get_node (node->thunk.alias),
			  NULL, 0, CGRAPH_FREQ_BASE);
    }
  else
    {
      current_function_decl = decl;
      push_cfun (DECL_STRUCT_FUNCTION (decl));

      assign_assembler_name_if_neeeded (node->decl);


      if (!gimple_body (decl))
	gimplify_function_tree (decl);
      dump_function (TDI_generic, decl);

      cgraph_lower_function (node);
      pop_cfun ();
    }
  node->analyzed = true;

  current_function_decl = save;
}
