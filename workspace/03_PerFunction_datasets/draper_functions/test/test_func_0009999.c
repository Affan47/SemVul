find_aggregate_values_for_callers_subset (struct cgraph_node *node,
					  vec<cgraph_edge_p> callers)
{
  struct ipa_node_params *dest_info = IPA_NODE_REF (node);
  struct ipa_agg_replacement_value *res = NULL;
  struct cgraph_edge *cs;
  int i, j, count = ipa_get_param_count (dest_info);

  FOR_EACH_VEC_ELT (callers, j, cs)
    {
      int c = ipa_get_cs_argument_count (IPA_EDGE_REF (cs));
      if (c < count)
	count = c;
    }

  for (i = 0; i < count ; i++)
    {
      struct cgraph_edge *cs;
      vec<ipa_agg_jf_item_t> inter = vNULL;
      struct ipa_agg_jf_item *item;
      struct ipcp_param_lattices *plats = ipa_get_parm_lattices (dest_info, i);
      int j;


      if (plats->aggs_bottom)
	continue;

      FOR_EACH_VEC_ELT (callers, j, cs)
	{
	  inter = intersect_aggregates_with_edge (cs, i, inter);

	  if (!inter.exists ())
	    goto next_param;
	}

      FOR_EACH_VEC_ELT (inter, j, item)
	{
	  struct ipa_agg_replacement_value *v;

	  if (!item->value)
	    continue;

	  v = ggc_alloc_ipa_agg_replacement_value ();
	  v->index = i;
	  v->offset = item->offset;
	  v->value = item->value;
	  v->by_ref = plats->aggs_by_ref;
	  v->next = res;
	  res = v;
	}

    next_param:
      if (inter.exists ())
	inter.release ();
    }
  return res;
}
