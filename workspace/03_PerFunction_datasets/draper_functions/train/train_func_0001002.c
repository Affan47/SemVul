find_def_preds (VEC(use_pred_info_t, heap) ***preds,
                size_t *num_preds, gimple phi)
{
  size_t num_chains = 0, i, n;
  VEC(edge, heap) **dep_chains = 0;
  VEC(edge, heap) *cur_chain = 0;
  VEC(edge, heap) *def_edges = 0;
  bool has_valid_pred = false;
  basic_block phi_bb, cd_root = 0;
  struct pointer_set_t *visited_phis;

  dep_chains = XCNEWVEC (VEC(edge, heap) *, MAX_NUM_CHAINS);

  phi_bb = gimple_bb (phi);


  cd_root = find_dom (phi_bb);
  if (!cd_root)
    return false;

  visited_phis = pointer_set_create ();
  collect_phi_def_edges (phi, cd_root, &def_edges, visited_phis);
  pointer_set_destroy (visited_phis);

  n = VEC_length (edge, def_edges);
  if (n == 0)
    return false;

  for (i = 0; i < n; i++)
    {
      size_t prev_nc, j;
      edge opnd_edge;

      opnd_edge = VEC_index (edge, def_edges, i);
      prev_nc = num_chains;
      compute_control_dep_chain (cd_root, opnd_edge->src,
                                 dep_chains, &num_chains,
                                 &cur_chain);

      VEC_free (edge, heap, cur_chain);
      cur_chain = 0;


      if (EDGE_COUNT (opnd_edge->src->succs) > 1)
        {
          if (prev_nc == num_chains
              && num_chains < MAX_NUM_CHAINS)
            num_chains++;
          for (j = prev_nc; j < num_chains; j++)
            {
              VEC_safe_push (edge, heap, dep_chains[j], opnd_edge);
            }
        }
    }

  has_valid_pred
      = convert_control_dep_chain_into_preds (dep_chains,
                                              num_chains,
                                              preds,
                                              num_preds);
  for (i = 0; i < num_chains; i++)
      VEC_free (edge, heap, dep_chains[i]);
  free (dep_chains);
  return has_valid_pred;
}
