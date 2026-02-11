ipcp_generate_summary (void)
{
  struct cgraph_node *node;

  if (dump_file)
    fprintf (dump_file, "\nIPA constant propagation start:\n");
  ipa_register_cgraph_hooks ();

  FOR_EACH_FUNCTION_WITH_GIMPLE_BODY (node)
      {
	node->local.versionable
	  = tree_versionable_function_p (node->symbol.decl);
	ipa_analyze_node (node);
      }
}
