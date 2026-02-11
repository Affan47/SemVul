event_master_event_fetch (struct event_master *em, struct event *fetch)
{
  int num;
  struct event *e;
  struct timeval tv = {0, 0};
  struct timeval *tv_wait;

  while (1)
    {
      struct epoll_event events[EPOLL_MAX_EVENTS];


      if ((e = event_list_pop_front (&em->el_ready)))
        {
          *fetch = *e;
          event_push_unused_list (e);
          return e;
        }


      event_list_event_process (&em->el_event);


      event_list_timer_wait (&em->el_timer, &tv);
      int msecs = tv.tv_sec * 1000 + tv.tv_usec / 1000;

      int num = epoll_wait (em->epoll_fd, events, EPOLL_MAX_EVENTS, msecs);
      if (num < 0)
        {
          logger_err (em->reg->lg, "Event Master: epoll_wait() error: %s",
                      strerror (errno));


          return NULL;
        }

      struct timeval tv_now;
      gettimeofday (&tv_now, NULL);
      event_list_timer_process (&em->el_timer, &tv_now);

      if (num > 0)
        {
          int i;


          for (i = 0; i < num; i++)
            {
              struct event *e = (struct event *)events[i].data.ptr;
              struct event_list *el;

              if (events[i].data.u32 == EVENT_TYPE_READ)
                el = &em->el_read;
              else
                el = &em->el_write;

              event_list_pop (el, e);
              event_list_push_back (&em->el_ready, e);
              event_set_ready (e);
            }
        }
    }


  return NULL;
}
