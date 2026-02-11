g_list_prepend (GList	 *list,
		gpointer  data)
{
  GList *new_list;

  new_list = _g_list_alloc ();
  new_list->data = data;
  new_list->next = list;

  if (list)
    {
      new_list->prev = list->prev;
      if (list->prev)
	list->prev->next = new_list;
      list->prev = new_list;
    }
  else
    new_list->prev = NULL;

  return new_list;
}
