cbf_rewind_category (cbf_handle handle)
{
  cbf_node *node;

  cbf_node *child_node;

  int i;

  if (!handle)

    return CBF_ARGUMENT;


  if (cbf_find_parent (&node, handle->node, CBF_SAVEFRAME)) {

    cbf_failnez (cbf_find_parent (&node, handle->node, CBF_DATABLOCK))

  }


  for (i = 0; (unsigned int)i < node->children; i++) {

    cbf_failnez (cbf_get_child (&child_node, node, i))

    if (child_node && child_node->type == CBF_CATEGORY) {

      handle->node = child_node;


      return 0;

    }
  }

  return CBF_NOTFOUND;

}
