atspi_init (void)
{
  char *match;
  const gchar *no_cache;

  if (atspi_inited)
    {
      return 1;
    }

  atspi_inited = TRUE;

  g_type_init ();

  _atspi_get_live_refs();

  bus = atspi_get_a11y_bus ();
  if (!bus)
    return 2;
  dbus_bus_register (bus, NULL);
  atspi_dbus_connection_setup_with_g_main(bus, g_main_context_default());
  dbus_connection_add_filter (bus, atspi_dbus_filter, NULL, NULL);
  match = g_strdup_printf ("type='signal',interface='%s',member='AddAccessible'", atspi_interface_cache);
  dbus_bus_add_match (bus, match, NULL);
  g_free (match);
  match = g_strdup_printf ("type='signal',interface='%s',member='RemoveAccessible'", atspi_interface_cache);
  dbus_bus_add_match (bus, match, NULL);
  g_free (match);
  match = g_strdup_printf ("type='signal',interface='%s',member='ChildrenChanged'", atspi_interface_event_object);
  dbus_bus_add_match (bus, match, NULL);
  g_free (match);
  match = g_strdup_printf ("type='signal',interface='%s',member='PropertyChange'", atspi_interface_event_object);
  dbus_bus_add_match (bus, match, NULL);
  g_free (match);
  match = g_strdup_printf ("type='signal',interface='%s',member='StateChanged'", atspi_interface_event_object);
  dbus_bus_add_match (bus, match, NULL);
  g_free (match);

  dbus_bus_add_match (bus,
                      "type='signal', interface='org.freedesktop.DBus', member='NameOwnerChanged'",
                      NULL);

  no_cache = g_getenv ("ATSPI_NO_CACHE");
  if (no_cache && g_strcmp0 (no_cache, "0") != 0)
    atspi_no_cache = TRUE;

  deferred_messages = g_queue_new ();

  return 0;
}
