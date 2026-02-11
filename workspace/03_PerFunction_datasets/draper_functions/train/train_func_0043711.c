make_tm_edge (gimple stmt, basic_block bb, struct tm_region *region)
{
  void **slot;
  struct tm_restart_node *n, dummy;

  if (cfun->gimple_df->tm_restart == NULL)
    cfun->gimple_df->tm_restart = htab_create_ggc (31, struct_ptr_hash,
						   struct_ptr_eq, ggc_free);

  dummy.stmt = stmt;
  dummy.label_or_list = gimple_block_label (region->entry_block);
  slot = htab_find_slot (cfun->gimple_df->tm_restart, &dummy, INSERT);
  n = (struct tm_restart_node *) *slot;
  if (n == NULL)
    {
      n = ggc_alloc_tm_restart_node ();
      *n = dummy;
    }
  else
    {
      tree old = n->label_or_list;
      if (TREE_CODE (old) == LABEL_DECL)
	old = tree_cons (NULL, old, NULL);
      n->label_or_list = tree_cons (NULL, dummy.label_or_list, old);
    }

  make_edge (bb, region->entry_block, EDGE_ABNORMAL | EDGE_ABNORMAL_CALL);
}
