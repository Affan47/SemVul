g_list_remove_nth (GList * list, gint indx)
{
  GList *tmp = list;
  gint k = 0;

  while (tmp) {
    if (k != indx)
      tmp = tmp->next;
    else {
      if (tmp->prev)
        tmp->prev->next = tmp->next;
      if (tmp->next)
        tmp->next->prev = tmp->prev;

      if (list == tmp)
        list = list->next;

      g_list_free_1 (tmp);
      break;
    }
    k++;
  }
  return list;
}
