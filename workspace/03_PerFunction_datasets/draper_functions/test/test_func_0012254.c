cbf_count_categories (cbf_handle handle, unsigned int *categories)
{
  cbf_node *node;

  if (!handle)

    return CBF_ARGUMENT;


  if (cbf_find_parent (&node, handle->node, CBF_SAVEFRAME)) {

    cbf_failnez (cbf_find_parent (&node, handle->node, CBF_DATABLOCK))

  }


  return cbf_count_typed_children (categories, node, CBF_CATEGORY);
}
