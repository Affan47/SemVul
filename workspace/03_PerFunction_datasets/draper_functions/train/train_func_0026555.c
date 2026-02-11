collect_phi_def_edges (gimple phi, basic_block cd_root,
                       vec<edge> *edges,
                       struct pointer_set_t *visited_phis)
{
  size_t i, n;
  edge opnd_edge;
  tree opnd;

  if (pointer_set_insert (visited_phis, phi))
    return;

  n = gimple_phi_num_args (phi);
  for (i = 0; i < n; i++)
    {
      opnd_edge = gimple_phi_arg_edge (phi, i);
      opnd = gimple_phi_arg_def (phi, i);

      if (TREE_CODE (opnd) != SSA_NAME)
        {
          if (dump_file && (dump_flags & TDF_DETAILS))
            {
              fprintf (dump_file, "\n[CHECK] Found def edge %d in ", (int)i);
              print_gimple_stmt (dump_file, phi, 0, 0);
            }
          edges->safe_push (opnd_edge);
        }
      else
        {
          gimple def = SSA_NAME_DEF_STMT (opnd);

          if (gimple_code (def) == GIMPLE_PHI
              && dominated_by_p (CDI_DOMINATORS,
                                 gimple_bb (def), cd_root))
            collect_phi_def_edges (def, cd_root, edges,
                                   visited_phis);
          else if (!uninit_undefined_value_p (opnd))
            {
              if (dump_file && (dump_flags & TDF_DETAILS))
                {
                  fprintf (dump_file, "\n[CHECK] Found def edge %d in ", (int)i);
                  print_gimple_stmt (dump_file, phi, 0, 0);
                }
              edges->safe_push (opnd_edge);
            }
        }
    }
}
