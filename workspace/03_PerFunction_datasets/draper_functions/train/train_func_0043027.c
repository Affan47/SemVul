handle_no_address_safety_analysis_attribute (tree *node, tree name, tree, int,
					     bool *no_add_attrs)
{
  if (TREE_CODE (*node) != FUNCTION_DECL)
    warning (OPT_Wattributes, "%qE attribute ignored", name);
  else if (!lookup_attribute ("no_sanitize_address", DECL_ATTRIBUTES (*node)))
    DECL_ATTRIBUTES (*node)
      = tree_cons (get_identifier ("no_sanitize_address"),
		   NULL_TREE, DECL_ATTRIBUTES (*node));
  *no_add_attrs = true;
  return NULL_TREE;
}
