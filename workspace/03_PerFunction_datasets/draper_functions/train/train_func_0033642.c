gc_transfer (struct gc_arena *dest, struct gc_arena *src)
{
  if (dest && src)
    {
      struct gc_entry *e = src->list;
      if (e)
	{
	  while (e->next != NULL)
	    e = e->next;
	  e->next = dest->list;
	  dest->list = src->list;
	  src->list = NULL;
	}
    }
}
