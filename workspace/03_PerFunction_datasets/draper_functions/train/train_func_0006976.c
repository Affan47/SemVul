cbf_next_saveframe (cbf_handle handle)
{
  cbf_node *parent, *node;

  int i;

  unsigned int index;

  if (!handle)

    return CBF_ARGUMENT;


  cbf_failnez (cbf_find_parent (&node, handle->node, CBF_SAVEFRAME))


  cbf_failnez (cbf_find_parent (&parent, node, CBF_DATABLOCK))


  cbf_failnez (cbf_child_index (&index, node))


  for (i = index+1; (unsigned int)i<parent->children; i++) {

    cbf_failnez (cbf_get_child (&node, parent, i))

    if (node->type == CBF_SAVEFRAME) {

      handle->node = node;


      return 0;
    }

  }

  return CBF_NOTFOUND;
}
