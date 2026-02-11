gamgi_engine_slist_invert (gamgi_slist *start)
{
gamgi_slist *slist, *slist_before, *slist_next;

slist_before = NULL;
for (slist = start; slist != NULL; slist = slist_next)
  {
  slist_next = slist->next;
  slist->next = slist_before;
  slist_before = slist;
  }

return slist_before;
}
