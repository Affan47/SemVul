ipa_read_node_info (struct lto_input_block *ib, struct cgraph_node *node,
		    struct data_in *data_in)
{
  struct ipa_node_params *info = IPA_NODE_REF (node);
  int k;
  struct cgraph_edge *e;
  struct bitpack_d bp;

  ipa_initialize_node_params (node);

  bp = lto_input_bitpack (ib);
  info->called_with_var_arguments = bp_unpack_value (&bp, 1);
  if (ipa_get_param_count (info) != 0)
    info->uses_analysis_done = true;
  info->node_enqueued = false;
  for (k = 0; k < ipa_get_param_count (info); k++)
    info->params[k].used = bp_unpack_value (&bp, 1);
  for (e = node->callees; e; e = e->next_callee)
    {
      struct ipa_edge_args *args = IPA_EDGE_REF (e);
      int count = lto_input_uleb128 (ib);

      ipa_set_cs_argument_count (args, count);
      if (!count)
	continue;

      args->jump_functions = ggc_alloc_cleared_vec_ipa_jump_func
	(ipa_get_cs_argument_count (args));
      for (k = 0; k < ipa_get_cs_argument_count (args); k++)
	ipa_read_jump_function (ib, ipa_get_ith_jump_func (args, k), data_in);
    }
  for (e = node->indirect_calls; e; e = e->next_callee)
    ipa_read_indirect_edge_info (ib, data_in, e);
}
