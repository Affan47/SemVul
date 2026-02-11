unnest_nesting_tree_1 (struct nesting_info *root)
{
  struct cgraph_node *node = cgraph_node (root->context);


  if (node->origin)
    {
       cgraph_unnest_node (cgraph_node (root->context));
       cgraph_finalize_function (root->context, true);
    }
}
