on_web_view_navigation_policy_decision_requested (WebKitWebView             *webView,
                                                  WebKitWebFrame            *frame,
                                                  WebKitNetworkRequest      *request,
                                                  WebKitWebNavigationAction *navigation_action,
                                                  WebKitWebPolicyDecision   *policy_decision,
                                                  gpointer                   user_data)
{
  GoaOAuth2Provider *provider = GOA_OAUTH2_PROVIDER (user_data);
  GoaOAuth2ProviderPrivate *priv = provider->priv;
  GHashTable *key_value_pairs;
  SoupMessage *message;
  SoupURI *uri;
  const gchar *fragment;
  const gchar *oauth2_error;
  const gchar *query;
  const gchar *redirect_uri;
  const gchar *requested_uri;
  gint response_id;


  requested_uri = webkit_network_request_get_uri (request);
  redirect_uri = goa_oauth2_provider_get_redirect_uri (provider);
  if (!g_str_has_prefix (requested_uri, redirect_uri))
    goto default_behaviour;

  message = webkit_network_request_get_message (request);
  uri = soup_message_get_uri (message);
  fragment = soup_uri_get_fragment (uri);
  query = soup_uri_get_query (uri);


  if (fragment != NULL)
    {


      key_value_pairs = soup_form_decode (fragment);


      priv->access_token = g_strdup (g_hash_table_lookup (key_value_pairs, "access_token"));
      if (priv->access_token != NULL)
        {
          gchar *expires_in_str = NULL;

          expires_in_str = g_hash_table_lookup (key_value_pairs, "expires_in");

          if (expires_in_str == NULL)
            expires_in_str = g_hash_table_lookup (key_value_pairs, "expires");

          if (expires_in_str != NULL)
            priv->access_token_expires_in = atoi (expires_in_str);

          priv->refresh_token = g_strdup (g_hash_table_lookup (key_value_pairs, "refresh_token"));

          response_id = GTK_RESPONSE_OK;
        }
      g_hash_table_unref (key_value_pairs);
    }

  if (priv->access_token != NULL)
    goto ignore_request;

  if (query != NULL)
    {
      key_value_pairs = soup_form_decode (query);

      priv->authorization_code = g_strdup (g_hash_table_lookup (key_value_pairs, "code"));
      if (priv->authorization_code != NULL)
        response_id = GTK_RESPONSE_OK;

      g_hash_table_unref (key_value_pairs);
    }

  if (priv->authorization_code != NULL)
    goto ignore_request;


  key_value_pairs = soup_form_decode (query);
  oauth2_error = (const gchar *) g_hash_table_lookup (key_value_pairs, "error");
  if (g_strcmp0 (oauth2_error, GOA_OAUTH2_ACCESS_DENIED) == 0)
    response_id = GTK_RESPONSE_CANCEL;
  else
    {
      g_set_error (&priv->error,
                   GOA_ERROR,
                   GOA_ERROR_NOT_AUTHORIZED,
                   _("Authorization response was \"%s\""),
                   oauth2_error);
      response_id = GTK_RESPONSE_CLOSE;
    }
  g_hash_table_unref (key_value_pairs);
  goto ignore_request;

 ignore_request:
  gtk_dialog_response (priv->dialog, response_id);
  webkit_web_policy_decision_ignore (policy_decision);
  return TRUE;

 default_behaviour:
  return FALSE;
}
