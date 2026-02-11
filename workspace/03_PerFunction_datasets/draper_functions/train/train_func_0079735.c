event_master_add_write (struct event_master *em, struct event *e,
                        EventCallback func, void *arg, int fd)
{
  struct epoll_event ev;

  if (fd < 0)
    return NULL;

  if (e == NULL)
    {
      e = event_master_event_get (em, EVENT_TYPE_WRITE, func, arg);
      if (e == NULL)
        return NULL;

      event_set_epoll_write (e, &ev);

      if (epoll_ctl (em->epoll_fd, EPOLL_CTL_ADD, fd, &ev) < 0)
        {
          logger_err (em->reg->lg, "Event Master: epoll_ctl() error: %s",
                      strerror (errno));


          return NULL;
        }

      e->u.fd = fd;
    }

  e->arg = arg;
  event_list_push_back (&em->el_write, e);

  return e;
}
