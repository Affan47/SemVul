gamgi_engine_dlist_merge (gamgi_dlist *a,
gamgi_dlist *b, int (* function) (const void *, const void *))
{
gamgi_dlist start;
gamgi_dlist *c = &start;

while (a != NULL && b != NULL)
  if ((*function) (a, b) > 0)
    { c->next = b; b->before = c; c = b; b = b->next; }
  else
    { c->next = a; a->before = c; c = a; a = a->next; }
c->next = (a == NULL) ? b : a;

return start.next;
}
