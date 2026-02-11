insert_phi_nodes (bitmap_head *dfs)
{
  referenced_var_iterator rvi;
  bitmap_iterator bi;
  tree var;
  bitmap vars;
  unsigned uid;

  timevar_push (TV_TREE_INSERT_PHI_NODES);


  vars = BITMAP_ALLOC (NULL);
  FOR_EACH_REFERENCED_VAR (cfun, var, rvi)
    {
      struct def_blocks_d *def_map;

      def_map = find_def_blocks_for (var);
      if (def_map == NULL)
	continue;

      if (get_phi_state (var) != NEED_PHI_STATE_NO)
	bitmap_set_bit (vars, DECL_UID (var));
    }

  EXECUTE_IF_SET_IN_BITMAP (vars, 0, uid, bi)
    {
      tree var = referenced_var (uid);
      struct def_blocks_d *def_map;
      bitmap idf;

      def_map = find_def_blocks_for (var);
      idf = compute_idf (def_map->def_blocks, dfs);
      insert_phi_nodes_for (var, idf, false);
      BITMAP_FREE (idf);
    }

  BITMAP_FREE (vars);

  timevar_pop (TV_TREE_INSERT_PHI_NODES);
}
