push_nested_class (tree type)
{
  tree context;


  if (type == NULL_TREE
      || type == error_mark_node
      || TREE_CODE (type) == NAMESPACE_DECL
      || ! IS_AGGR_TYPE (type)
      || TREE_CODE (type) == TEMPLATE_TYPE_PARM
      || TREE_CODE (type) == BOUND_TEMPLATE_TEMPLATE_PARM)
    return;

  context = DECL_CONTEXT (TYPE_MAIN_DECL (type));

  if (context && CLASS_TYPE_P (context))
    push_nested_class (context);
  pushclass (type);
}
