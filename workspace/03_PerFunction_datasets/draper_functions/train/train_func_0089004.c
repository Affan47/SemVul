on_notify_authority_owner (GObject    *object,
                           GParamSpec *pspec,
                           gpointer    user_data)
{
  Server *server = user_data;
  gchar *owner;

  owner = polkit_authority_get_owner (server->authority);
  if (owner == NULL)
    {
      g_printerr ("PolicyKit daemon disconnected from the bus.\n");

      if (server->is_registered)
        g_printerr ("We are no longer a registered authentication agent.\n");

      server->is_registered = FALSE;
    }
  else
    {

      if (!server->is_registered)
        {
          GError *error;

          g_printerr ("PolicyKit daemon reconnected to bus.\n");
          g_printerr ("Attempting to re-register as an authentication agent.\n");

          error = NULL;
          if (server_register (server, &error))
            {
              g_printerr ("We are now a registered authentication agent.\n");
            }
          else
            {
              g_printerr ("Failed to register as an authentication agent: %s\n", error->message);
              g_error_free (error);
            }
        }
    }
  g_free (owner);
}
