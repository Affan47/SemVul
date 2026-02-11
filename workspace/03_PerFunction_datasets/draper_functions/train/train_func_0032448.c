compute_pre_data (void)
{
  basic_block bb;

  compute_local_properties (transp, comp, antloc, &expr_hash_table);
  prune_expressions (true);
  sbitmap_vector_zero (ae_kill, last_basic_block);


  FOR_EACH_BB (bb)
    {
      sbitmap_a_or_b (ae_kill[bb->index], transp[bb->index], comp[bb->index]);
      sbitmap_not (ae_kill[bb->index], ae_kill[bb->index]);
    }

  edge_list = pre_edge_lcm (expr_hash_table.n_elems, transp, comp, antloc,
			    ae_kill, &pre_insert_map, &pre_delete_map);
  sbitmap_vector_free (antloc);
  antloc = NULL;
  sbitmap_vector_free (ae_kill);
  ae_kill = NULL;

  prune_insertions_deletions (expr_hash_table.n_elems);
}
