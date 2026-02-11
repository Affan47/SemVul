on_handle_get_access_token (GoaOAuthBased         *interface,
                            GDBusMethodInvocation *invocation,
                            gpointer               user_data)
{
  GoaObject *object;
  GoaAccount *account;
  GoaProvider *provider;
  GError *error;
  gchar *access_token;
  gchar *access_token_secret;
  gint access_token_expires_in;


  access_token = NULL;
  access_token_secret = NULL;

  object = GOA_OBJECT (g_dbus_interface_get_object (G_DBUS_INTERFACE (interface)));
  account = goa_object_peek_account (object);
  provider = goa_provider_get_for_provider_type (goa_account_get_provider_type (account));

  error = NULL;
  access_token = goa_oauth_provider_get_access_token_sync (GOA_OAUTH_PROVIDER (provider),
                                                                   object,
                                                                   FALSE,
                                                                   &access_token_secret,
                                                                   &access_token_expires_in,
                                                                   NULL,
                                                                   &error);
  if (access_token == NULL)
    {
      g_dbus_method_invocation_return_gerror (invocation, error);
      g_error_free (error);
    }
  else
    {
      goa_oauth_based_complete_get_access_token (interface,
                                                 invocation,
                                                 access_token,
                                                 access_token_secret,
                                                 access_token_expires_in);
    }
  g_free (access_token);
  g_free (access_token_secret);
  g_object_unref (provider);
  return TRUE;
}
