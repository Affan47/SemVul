ipa_print_node_params (FILE *f, struct cgraph_node *node)
{
  int i, count;
  tree temp;
  struct ipa_node_params *info;

  if (!node->analyzed)
    return;
  info = IPA_NODE_REF (node);
  fprintf (f, "  function  %s parameter descriptors:\n",
	   cgraph_node_name (node));
  count = ipa_get_param_count (info);
  for (i = 0; i < count; i++)
    {
      temp = ipa_get_param (info, i);
      if (TREE_CODE (temp) == PARM_DECL)
	fprintf (f, "    param %d : %s", i,
                 (DECL_NAME (temp)
                  ? (*lang_hooks.decl_printable_name) (temp, 2)
                  : "(unnamed)"));
      if (ipa_is_param_used (info, i))
	fprintf (f, " used");
      fprintf (f, "\n");
    }
}
