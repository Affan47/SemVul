set_transport_settings (GdictSourceDialog *dialog)
{
  switch (dialog->transport)
    {
    case GDICT_SOURCE_TRANSPORT_DICTD:
      {
        GdictClientContext *context;
        const gchar *hostname;
        gchar *port_str;
        guint port;

        context = GDICT_CLIENT_CONTEXT (dialog->context);
        hostname = gdict_client_context_get_hostname (context);
        port = gdict_client_context_get_port (context);
        port_str = g_strdup_printf ("%d", port);

        set_text_to_entry (dialog, "hostname_entry", hostname);
        set_text_to_entry (dialog, "port_entry", port_str);

        gtk_widget_show (GTK_WIDGET (gtk_builder_get_object (dialog->builder, "hostname_label")));
        gtk_widget_show (GTK_WIDGET (gtk_builder_get_object (dialog->builder, "hostname_entry")));
        gtk_widget_show (GTK_WIDGET (gtk_builder_get_object (dialog->builder, "port_label")));
        gtk_widget_show (GTK_WIDGET (gtk_builder_get_object (dialog->builder, "port_entry")));

        g_free (port_str);
      }
      break;
    case GDICT_SOURCE_TRANSPORT_INVALID:
    default:
      break;
    }
}
