tree_ssa_strlen (void)
{
  struct dom_walk_data walk_data;

  VEC_safe_grow_cleared (int, heap, ssa_ver_to_stridx, num_ssa_names);
  max_stridx = 1;
  strinfo_pool = create_alloc_pool ("strinfo_struct pool",
				    sizeof (struct strinfo_struct), 64);

  calculate_dominance_info (CDI_DOMINATORS);


  walk_data.dom_direction = CDI_DOMINATORS;
  walk_data.initialize_block_local_data = NULL;
  walk_data.before_dom_children = strlen_enter_block;
  walk_data.after_dom_children = strlen_leave_block;
  walk_data.block_local_data_size = 0;
  walk_data.global_data = NULL;


  init_walk_dominator_tree (&walk_data);


  walk_dominator_tree (&walk_data, ENTRY_BLOCK_PTR);


  fini_walk_dominator_tree (&walk_data);

  VEC_free (int, heap, ssa_ver_to_stridx);
  free_alloc_pool (strinfo_pool);
  if (decl_to_stridxlist_htab)
    {
      obstack_free (&stridx_obstack, NULL);
      htab_delete (decl_to_stridxlist_htab);
      decl_to_stridxlist_htab = NULL;
    }
  laststmt.stmt = NULL;
  laststmt.len = NULL_TREE;
  laststmt.stridx = 0;

  return 0;
}
