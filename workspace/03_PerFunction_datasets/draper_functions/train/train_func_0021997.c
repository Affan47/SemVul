execute_sm (struct loop *loop, vec<edge> exits, mem_ref_p ref)
{
  tree tmp_var, store_flag;
  unsigned i;
  gimple load;
  struct fmt_data fmt_data;
  edge ex, latch_edge;
  struct lim_aux_data *lim_data;
  bool multi_threaded_model_p = false;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Executing store motion of ");
      print_generic_expr (dump_file, ref->mem, 0);
      fprintf (dump_file, " from loop %d\n", loop->num);
    }

  tmp_var = create_tmp_reg (TREE_TYPE (ref->mem),
			      get_lsm_tmp_name (ref->mem, ~0));

  fmt_data.loop = loop;
  fmt_data.orig_loop = loop;
  for_each_index (&ref->mem, force_move_till, &fmt_data);

  if (block_in_transaction (loop_preheader_edge (loop)->src)
      || !PARAM_VALUE (PARAM_ALLOW_STORE_DATA_RACES))
    multi_threaded_model_p = true;

  if (multi_threaded_model_p)
    store_flag = execute_sm_if_changed_flag_set (loop, ref);

  rewrite_mem_refs (loop, ref, tmp_var);


  latch_edge = loop_latch_edge (loop);


  load = gimple_build_assign (tmp_var, unshare_expr (ref->mem));
  lim_data = init_lim_data (load);
  lim_data->max_loop = loop;
  lim_data->tgt_loop = loop;
  gsi_insert_on_edge (latch_edge, load);

  if (multi_threaded_model_p)
    {
      load = gimple_build_assign (store_flag, boolean_false_node);
      lim_data = init_lim_data (load);
      lim_data->max_loop = loop;
      lim_data->tgt_loop = loop;
      gsi_insert_on_edge (latch_edge, load);
    }


  FOR_EACH_VEC_ELT (exits, i, ex)
    if (!multi_threaded_model_p)
      {
	gimple store;
	store = gimple_build_assign (unshare_expr (ref->mem), tmp_var);
	gsi_insert_on_edge (ex, store);
      }
    else
      execute_sm_if_changed (ex, ref->mem, tmp_var, store_flag);
}
