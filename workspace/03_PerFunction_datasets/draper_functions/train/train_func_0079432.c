cbf_next_row (cbf_handle handle)
{
  cbf_node *node;

  unsigned int rows;

  if (!handle)

    return CBF_ARGUMENT;


  cbf_failnez (cbf_find_parent (&node, handle->node, CBF_COLUMN))

  cbf_failnez (cbf_count_children (&rows, node))


  if (handle->row >= rows)

    return CBF_NOTFOUND;

  handle->row++;

  handle->search_row = handle->row;


  return 0;
}
