dconf_engine_handle_dbus_signal (GBusType     bus_type,
                                 const gchar *bus_name,
                                 const gchar *object_path,
                                 const gchar *signal_name,
                                 GVariant    *parameters)
{
  g_assert (g_thread_self () != main_thread || okay_in_main);

  if (!dbus_thread)
    dbus_thread = g_thread_self ();
  g_assert (g_thread_self () == dbus_thread);

  if (g_str_equal (signal_name, "TestSignal"))
    {
      GVariant *expected;

      expected = g_variant_parse (NULL, "('1', ['2', '3'])", NULL, NULL, NULL);
      g_assert (g_variant_equal (parameters, expected));
      g_variant_unref (expected);

      signal_was_received = TRUE;
      g_idle_add (just_wake, NULL);
    }
}
