internal_clist_nth(clist * lst, int indx)
{
  clistiter * cur;

  cur = clist_begin(lst);
  while ((indx > 0) && (cur != NULL)) {
    cur = cur->next;
    indx --;
  }

  if (cur == NULL)
    return NULL;

  return cur;
}
