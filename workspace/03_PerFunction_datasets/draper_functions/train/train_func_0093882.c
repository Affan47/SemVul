_cdio_list_free (CdioList_t *p_list, int free_data)
{
  while (_cdio_list_length (p_list))
    _cdio_list_node_free (_cdio_list_begin (p_list), free_data);

  free (p_list);
}
