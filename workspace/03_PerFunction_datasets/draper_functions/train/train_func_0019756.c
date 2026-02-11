_init_inotify (BusContext *context)
{
  int ret = 0;

  if (inotify_fd == -1)
    {
#ifdef HAVE_INOTIFY_INIT1
      inotify_fd = inotify_init1 (IN_CLOEXEC);


      if (inotify_fd < 0)
        inotify_fd = inotify_init ();
#else
      inotify_fd = inotify_init ();
#endif
      if (inotify_fd <= 0)
        {
          _dbus_warn ("Cannot initialize inotify\n");
          goto out;
        }
      loop = bus_context_get_loop (context);
      _dbus_loop_ref (loop);

      watch = _dbus_watch_new (inotify_fd, DBUS_WATCH_READABLE, TRUE,
                               _handle_inotify_watch, NULL, NULL);

      if (watch == NULL)
        {
          _dbus_warn ("Unable to create inotify watch\n");
          goto out;
        }

      if (!_dbus_loop_add_watch (loop, watch))
        {
          _dbus_warn ("Unable to add reload watch to main loop");
          _dbus_watch_unref (watch);
          watch = NULL;
          goto out;
        }

      if (!_dbus_register_shutdown_func (_shutdown_inotify, NULL))
      {
          _dbus_warn ("Unable to register shutdown func");
          _dbus_watch_unref (watch);
          watch = NULL;
          goto out;
      }
    }

  ret = 1;

out:
  return ret;
}
