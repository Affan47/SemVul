_dbus_loop_dispatch (DBusLoop *loop)
{

#if MAINLOOP_SPEW
  _dbus_verbose ("  %d connections to dispatch\n", _dbus_list_get_length (&loop->need_dispatch));
#endif

  if (loop->need_dispatch == NULL)
    return FALSE;

 next:
  while (loop->need_dispatch != NULL)
    {
      DBusConnection *connection = _dbus_list_pop_first (&loop->need_dispatch);

      while (TRUE)
        {
          DBusDispatchStatus status;

          status = dbus_connection_dispatch (connection);

          if (status == DBUS_DISPATCH_COMPLETE)
            {
              dbus_connection_unref (connection);
              goto next;
            }
          else
            {
              if (status == DBUS_DISPATCH_NEED_MEMORY)
                _dbus_wait_for_memory ();
            }
        }
    }

  return TRUE;
}
