plain_sockets_thread_func (void *data)
{
  GMainContext *context;
  ClientData cd;
  int fd;
  struct sockaddr_un addr;
  GIOChannel *channel;
  GSource *gsource;

  g_printerr ("Starting client thread %p\n",
              g_thread_self());

  fd = socket (PF_UNIX, SOCK_STREAM, 0);

  if (fd < 0)
    {
      g_printerr ("Failed to create socket: %s",
                  strerror (errno));
      exit (1);
    }

  _DBUS_ZERO (addr);
  addr.sun_family = AF_UNIX;

#ifdef HAVE_ABSTRACT_SOCKETS


  addr.sun_path[0] = '\0';
  strncpy (&addr.sun_path[1], plain_sockets_address, _DBUS_MAX_SUN_PATH_LENGTH - 2);

#else
  strncpy (addr.sun_path, plain_sockets_address, _DBUS_MAX_SUN_PATH_LENGTH - 1);
#endif

  if (connect (fd, (struct sockaddr*) &addr, sizeof (addr)) < 0)
    {
      g_printerr ("Failed to connect to socket %s: %s",
                  plain_sockets_address, strerror (errno));
      exit (1);
    }

  context = g_main_context_new ();

  cd.iterations = 1;
  cd.loop = g_main_loop_new (context, FALSE);
  cd.vtable = data;

  channel = g_io_channel_unix_new (fd);

  gsource = g_io_create_watch (channel,
                               G_IO_IN | G_IO_OUT |
                               G_IO_ERR | G_IO_HUP | G_IO_NVAL | G_IO_PRI);

  g_source_set_callback (gsource,
                         (GSourceFunc)plain_sockets_client_side_watch,
                         &cd, NULL);

  g_source_attach (gsource, context);

  g_io_channel_unref (channel);

  g_printerr ("Client thread writing to prime pingpong\n");
  write_junk (fd, echo_call_size, cd.vtable->fake_malloc_overhead);
  g_printerr ("Client thread done writing primer\n");

  g_printerr ("Client thread entering main loop\n");
  g_main_loop_run (cd.loop);
  g_printerr ("Client thread %p exiting main loop\n",
              g_thread_self());

  g_source_destroy (gsource);

  close (fd);

  g_main_loop_unref (cd.loop);
  g_main_context_unref (context);

  return NULL;
}
