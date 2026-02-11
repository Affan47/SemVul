ipcp_initialize_node_lattices (struct cgraph_node *node)
{
  int i;
  struct ipa_node_params *info = IPA_NODE_REF (node);
  enum ipa_lattice_type type;

  if (ipa_is_called_with_var_arguments (info))
    type = IPA_BOTTOM;
  else if (node->local.local)
    type = IPA_TOP;


  else if (ipcp_cloning_candidate_p (node))
    type = IPA_TOP, n_cloning_candidates ++;
  else
    type = IPA_BOTTOM;

  for (i = 0; i < ipa_get_param_count (info) ; i++)
    {
      ipcp_get_lattice (info, i)->type = type;
      if (type == IPA_BOTTOM)
	ipa_set_param_cannot_devirtualize (info, i);
    }
}
