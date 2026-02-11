cbf_new_row (cbf_handle handle)
{
  cbf_node *node, *columnnode;

  int errorcode [2];

  unsigned int rows, columns, column;

  if (!handle)

    return CBF_ARGUMENT;


  cbf_failnez (cbf_find_parent (&node, handle->node, CBF_CATEGORY))


  cbf_failnez (cbf_count_rows (handle, &rows))

  cbf_failnez (cbf_count_columns (handle, &columns))


  for (column = 0; column < columns; column++)
  {
    errorcode [0] = cbf_get_child (&columnnode, node, column);

    if (!errorcode [0])

      errorcode [0] = cbf_add_columnrow (columnnode, NULL);

    if (errorcode [0])
    {


      while (column)
      {
        column--;

        errorcode [1] = cbf_get_child (&columnnode, node, column);

        if (!errorcode [1])

          errorcode [1] |= cbf_set_children (columnnode, rows);

        errorcode [0] |= errorcode [1];
      }

      return errorcode [0];
    }
  }


  handle->row = rows;

  handle->search_row = rows;

  return 0;
}
