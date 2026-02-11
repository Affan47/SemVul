grl_flickr_get_goa_multiple_config (GrlPlugin *plugin, gboolean public)
{
  GList *tmp;
  GList *list = NULL;
  GError *error = NULL;
  GrlConfig *conf = NULL;
  GList *configs = NULL;

  gchar *access_token;
  gchar *token_secret;

  gboolean public_created = FALSE;

  GoaAccount *acc = NULL;
  GoaOAuthBased *oauth = NULL;
  GoaClient *cl = goa_client_new_sync (NULL, &error);

  if (error != NULL)
  {
    GRL_ERROR ("%s\n", error->message);
    return NULL;
  }

  list = goa_client_get_accounts (cl);
  tmp = g_list_first (list);


  while (tmp != NULL)
  {
    acc = goa_object_peek_account (tmp->data);

    if (strcmp (goa_account_get_provider_type (acc), "flickr") == 0)
    {
      oauth = goa_object_peek_oauth_based (tmp->data);

      if (oauth != NULL)
      {
        conf = grl_config_new (grl_plugin_get_id (plugin),
                               NULL);


        grl_config_set_api_key (conf,
                                goa_oauth_based_get_consumer_key (oauth));
        grl_config_set_api_secret (conf,
                                   goa_oauth_based_get_consumer_secret (oauth));


        grl_config_set_string (conf, "goa-account-id",
                                      goa_account_get_id (acc));


        if (public == TRUE && public_created == FALSE)
        {
          configs = g_list_append (configs, conf);
          public_created = TRUE;

          continue;
        }


        if (! goa_oauth_based_call_get_access_token_sync (oauth,
                                                          &access_token,
                                                          &token_secret,
                                                          NULL, NULL,
                                                          &error))
        {


          GRL_INFO ("Access token: %s\n", error->message);
          g_error_free (error);
        }
        else
        {
          grl_config_set_api_token (conf, access_token);
          grl_config_set_api_token_secret (conf, token_secret);

          g_clear_pointer (&access_token, g_free);
          g_clear_pointer (&token_secret, g_free);
        }

        configs = g_list_append (configs, conf);
      }
    }
    tmp = g_list_next (tmp);
  }

  g_object_unref (cl);
  g_list_free_full (list, g_object_unref);

  return configs;
}
