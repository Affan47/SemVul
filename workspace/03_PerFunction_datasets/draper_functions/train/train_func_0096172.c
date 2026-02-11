MinItem(struct icon_info *head)
{
  struct icon_info *tmp, *i_min;

  if (head == NULL)
    return NULL;

  i_min = head;
  tmp = head->next;
  while (tmp != NULL){
    if (itemcmp(i_min, tmp) > 0)
      i_min = tmp;
    tmp = tmp->next;
  }
  return i_min;
}
