gconf_client_real_unreturned_error (GConfClient* client, GError* error)
{
  trace ("Unreturned error '%s'", error->message);
  if (client->error_mode == GCONF_CLIENT_HANDLE_UNRETURNED)
    {
      if (global_error_handler != NULL)
        {
          (*global_error_handler) (client, error);
        }
      else
        {


          if (error->code == GCONF_ERROR_OVERRIDDEN ||
              error->code == GCONF_ERROR_NO_WRITABLE_DATABASE)
            return;

          g_printerr (_("GConf Error: %s\n"),
                      error->message);
        }
    }
}
