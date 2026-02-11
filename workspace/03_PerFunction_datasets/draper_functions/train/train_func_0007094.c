on_activate_link (GtkLabel    *label,
                  const gchar *uri,
                  gpointer     user_data)
{
  GduWindow *window = GDU_WINDOW (user_data);
  gboolean handled = FALSE;

  if (g_str_has_prefix (uri, "x-udisks://"))
    {
      UDisksObject *object = udisks_client_peek_object (window->client, uri + strlen ("x-udisks://"));
      if (object != NULL)
        {
          select_object (window, object);
          handled = TRUE;
        }
    }

  return handled;
}
