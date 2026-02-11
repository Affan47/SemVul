dbus_message_finalize (DBusMessage *message)
{
  _dbus_assert (_dbus_atomic_get (&message->refcount) == 0);


  _dbus_data_slot_list_free (&message->slot_list);

  _dbus_list_foreach (&message->counters,
                      free_counter, message);
  _dbus_list_clear (&message->counters);

  _dbus_header_free (&message->header);
  _dbus_string_free (&message->body);

#ifdef HAVE_UNIX_FD_PASSING
  close_unix_fds(message->unix_fds, &message->n_unix_fds);
  dbus_free(message->unix_fds);
#endif

  _dbus_assert (_dbus_atomic_get (&message->refcount) == 0);

  dbus_free (message);
}
