finish_label_address_expr (tree label)
{
  tree result;

  if (pedantic)
    pedwarn ("taking the address of a label is non-standard");

  if (label == error_mark_node)
    return error_mark_node;

  label = lookup_label (label);
  if (label == NULL_TREE)
    result = null_pointer_node;
  else
    {
      TREE_USED (label) = 1;
      result = build1 (ADDR_EXPR, ptr_type_node, label);
      TREE_CONSTANT (result) = 1;


    }

  return result;
}
