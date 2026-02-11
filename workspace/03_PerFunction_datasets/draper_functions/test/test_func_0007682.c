event_list_timer_process (struct event_list *el, struct timeval *tv_now)
{
  struct event *e;
  struct event *next;
  int ready = 0;

  for (e = el->head; e; e = next)
    {
      next = e->next;
      if (timeval_cmp (*tv_now, event_sands (e)) < 0)
        return ready;

      event_list_pop (el, e);
      event_list_push_back (&e->master->el_ready, e);
      event_set_ready (e);
      ready++;
    }

  return ready;
}
