atspi_set_main_context (GMainContext *cnx)
{
  if (atspi_main_context == cnx)
    return;
  if (process_deferred_messages_source != NULL)
  {
    g_source_destroy (process_deferred_messages_source);
    g_source_unref (process_deferred_messages_source);
    process_deferred_messages_source = g_idle_source_new ();
    g_source_set_callback (process_deferred_messages_source,
                           process_deferred_messages_callback, NULL, NULL);
    g_source_attach (process_deferred_messages_source, cnx);
  }
  atspi_main_context = cnx;
  atspi_dbus_connection_setup_with_g_main (atspi_get_a11y_bus (), cnx);
}
