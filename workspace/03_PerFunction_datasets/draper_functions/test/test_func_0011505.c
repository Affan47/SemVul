fluid_list_remove_link(fluid_list_t *list, fluid_list_t *link)
{
  fluid_list_t *tmp;
  fluid_list_t *prev;

  prev = NULL;
  tmp = list;

  while (tmp) {
    if (tmp == link) {
      if (prev) {
	prev->next = tmp->next;
      }
      if (list == tmp) {
	list = list->next;
      }
      tmp->next = NULL;
      break;
    }

    prev = tmp;
    tmp = tmp->next;
  }

  return list;
}
