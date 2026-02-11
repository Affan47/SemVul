ipa_initialize_node_params (struct cgraph_node *node)
{
  struct ipa_node_params *info = IPA_NODE_REF (node);

  if (!info->descriptors.exists ())
    {
      int param_count;

      param_count = count_formal_params (node->symbol.decl);
      if (param_count)
	{
	  info->descriptors.safe_grow_cleared (param_count);
	  ipa_populate_param_decls (node, info->descriptors);
	}
    }
}
