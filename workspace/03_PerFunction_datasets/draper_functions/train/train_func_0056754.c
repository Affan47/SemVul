list_size (struct list_head *list)
{
  struct list_head *cur;

  int i = 0;
  list_for_each (cur, list)
    i++;

  return i;
}
