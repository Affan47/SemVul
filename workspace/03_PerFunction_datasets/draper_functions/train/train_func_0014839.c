socket_set_poll_poll (DBusSocketSet   *set,
                      DBusSocketEvent *revents,
                      int              max_events,
                      int              timeout_ms)
{
  DBusSocketSetPoll *self = socket_set_poll_cast (set);
  int i;
  int n_events;
  int n_ready;

  _dbus_assert (max_events > 0);

  for (i = 0; i < self->n_fds; i++)
    self->fds[i].revents = 0;

  n_ready = _dbus_poll (self->fds, self->n_fds, timeout_ms);

  if (n_ready <= 0)
    return n_ready;

  n_events = 0;

  for (i = 0; i < self->n_fds; i++)
    {
      if (self->fds[i].revents != 0)
        {
          revents[n_events].fd = self->fds[i].fd;
          revents[n_events].flags = watch_flags_from_poll_revents (self->fds[i].revents);

          n_events += 1;


          if (n_events == max_events)
            return n_events;
        }
    }

  return n_events;
}
