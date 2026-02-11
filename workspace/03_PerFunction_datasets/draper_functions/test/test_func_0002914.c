_cdio_list_append (CdioList_t *p_list, void *p_data)
{
  cdio_assert (p_list != NULL);

  if (p_list->length == 0)
    {
      _cdio_list_prepend (p_list, p_data);
    }
  else
    {
      CdioListNode_t *p_new_node = calloc (1, sizeof (CdioListNode_t));

      p_new_node->list = p_list;
      p_new_node->next = NULL;
      p_new_node->data = p_data;

      p_list->end->next = p_new_node;
      p_list->end = p_new_node;

      p_list->length++;
    }
}
