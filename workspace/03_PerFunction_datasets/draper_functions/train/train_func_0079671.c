event_master_event_get (struct event_master *em, event_type type,
                        EventCallback func, void *arg)
{
  struct event *e = event_list_pop_front (&em->el_unused);

  if (!e)
    {
      e = event_new ();
      e->master = em;
      em->count++;
    }

  e->type = type;
  e->func = func;
  e->arg = arg;

  return e;
}
