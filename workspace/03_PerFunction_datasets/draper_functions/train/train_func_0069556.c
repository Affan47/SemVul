socket_set_poll_add (DBusSocketSet  *set,
                     int             fd,
                     unsigned int    flags,
                     dbus_bool_t     enabled)
{
  DBusSocketSetPoll *self = socket_set_poll_cast (set);
#ifndef DBUS_DISABLE_ASSERT
  int i;

  for (i = 0; i < self->n_fds; i++)
    _dbus_assert (self->fds[i].fd != fd);
#endif

  if (self->n_reserved >= self->n_allocated)
    {
      DBusPollFD *new_fds = dbus_realloc (self->fds,
          sizeof (DBusPollFD) * (self->n_allocated + REALLOC_INCREMENT));

      _dbus_verbose ("inflating set %p from %d en/%d res/%d alloc to %d\n",
                     self, self->n_fds, self->n_reserved, self->n_allocated,
                     self->n_allocated + REALLOC_INCREMENT);

      if (new_fds == NULL)
        return FALSE;

      self->fds = new_fds;
      self->n_allocated += REALLOC_INCREMENT;
    }

  _dbus_verbose ("before adding fd %d to %p, %d en/%d res/%d alloc\n",
                 fd, self, self->n_fds, self->n_reserved, self->n_allocated);
  _dbus_assert (self->n_reserved >= self->n_fds);
  _dbus_assert (self->n_allocated > self->n_reserved);

  self->n_reserved++;

  if (enabled)
    {
      self->fds[self->n_fds].fd = fd;
      self->fds[self->n_fds].events = watch_flags_to_poll_events (flags);
      self->n_fds++;
    }

  return TRUE;
}
