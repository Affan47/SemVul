collect_ada_namespace (tree namespc, const char *source_file)
{
  if (!namespc)
    return;


  collect_ada_nodes (NAMESPACE_LEVEL (namespc)->names, source_file);


  collect_ada_namespace (TREE_CHAIN (namespc), source_file);


  collect_ada_namespace (NAMESPACE_LEVEL (namespc)->namespaces, source_file);
}
