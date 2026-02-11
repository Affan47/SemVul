finish_template_type_parm (tree aggr, tree identifier)
{
  if (aggr != class_type_node)
    {
      pedwarn ("template type parameters must use the keyword `class' or `typename'");
      aggr = class_type_node;
    }

  return build_tree_list (aggr, identifier);
}
