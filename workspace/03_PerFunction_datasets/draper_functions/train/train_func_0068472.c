static_count (gamgi_dlist *dlist_now, int *backward, int *forward)
{
gamgi_dlist *dlist;

*backward = 0;
dlist = dlist_now;
while (dlist->next != NULL)
  {
  (*backward)++;
  dlist = dlist->next;
  }

*forward = 0;
dlist = dlist_now;
while (dlist->before != NULL)
  {
  (*forward)++;
  dlist = dlist->before;
  }

}
