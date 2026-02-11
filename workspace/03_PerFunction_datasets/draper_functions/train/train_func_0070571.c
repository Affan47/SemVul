ipa_tm_transform_calls_redirect (struct cgraph_node *node,
				 struct tm_region *region,
				 gimple_stmt_iterator *gsi,
				 bool *need_ssa_rename_p)
{
  gimple stmt = gsi_stmt (*gsi);
  struct cgraph_node *new_node;
  struct cgraph_edge *e = cgraph_edge (node, stmt);
  tree fndecl = gimple_call_fndecl (stmt);


  if (fndecl == NULL)
    {
      *need_ssa_rename_p |=
	ipa_tm_insert_gettmclone_call (node, region, gsi, stmt);
      return;
    }


  if (flags_from_decl_or_type (fndecl) & ECF_TM_BUILTIN)
    return;


  if (e->caller == e->callee && decl_is_tm_clone (current_function_decl))
    {
      gimple_call_set_fndecl (stmt, current_function_decl);
      return;
    }


  fndecl = find_tm_replacement_function (fndecl);
  if (fndecl)
    {
      new_node = cgraph_get_create_node (fndecl);


      new_node->local.tm_may_enter_irr = 1;
    }
  else
    {
      struct tm_ipa_cg_data *d;
      struct cgraph_node *tnode = e->callee;

      d = get_cg_data (&tnode, true);
      new_node = d->clone;


      if (new_node == NULL)
	{
	  *need_ssa_rename_p |=
	    ipa_tm_insert_gettmclone_call (node, region, gsi, stmt);
	  return;
	}

      fndecl = new_node->symbol.decl;
    }

  cgraph_redirect_edge_callee (e, new_node);
  gimple_call_set_fndecl (stmt, fndecl);
}
