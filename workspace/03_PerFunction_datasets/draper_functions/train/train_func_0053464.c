array_list_free (ArrayList *list)
{
  if (list->items)
  {
    free (list->items);

    list->items = NULL;
    list->item_count = 0;
  }
}
