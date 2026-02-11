get_identity_sync (GoaOAuthProvider  *provider,
                   const gchar       *access_token,
                   const gchar       *access_token_secret,
                   gchar            **out_presentation_identity,
                   GCancellable      *cancellable,
                   GError           **error)
{
  GError *identity_error;
  RestProxy *proxy;
  RestProxyCall *call;
  JsonParser *parser;
  JsonObject *json_object;
  gchar *ret;
  gchar *id;
  gchar *presentation_identity;

  ret = NULL;

  identity_error = NULL;
  proxy = NULL;
  call = NULL;
  parser = NULL;
  id = NULL;
  presentation_identity = NULL;


  proxy = oauth_proxy_new_with_token (goa_oauth_provider_get_consumer_key (provider),
                                      goa_oauth_provider_get_consumer_secret (provider),
                                      access_token,
                                      access_token_secret,
                                      "https://api.twitter.com/1/account/verify_credentials.json",
                                      FALSE);
  call = rest_proxy_new_call (proxy);
  rest_proxy_call_add_param (call, "skip_status", "true");

  if (!rest_proxy_call_sync (call, error))
    goto out;
  if (rest_proxy_call_get_status_code (call) != 200)
    {
      g_set_error (error,
                   GOA_ERROR,
                   GOA_ERROR_FAILED,
                   _("Expected status 200 when requesting guid, instead got status %d (%s)"),
                   rest_proxy_call_get_status_code (call),
                   rest_proxy_call_get_status_message (call));
      goto out;
    }

  parser = json_parser_new ();
  if (!json_parser_load_from_data (parser,
                                   rest_proxy_call_get_payload (call),
                                   rest_proxy_call_get_payload_length (call),
                                   &identity_error))
    {
      goa_warning ("json_parser_load_from_data() failed: %s (%s, %d)",
                   identity_error->message,
                   g_quark_to_string (identity_error->domain),
                   identity_error->code);
      g_set_error (error,
                   GOA_ERROR,
                   GOA_ERROR_FAILED,
                   _("Could not parse response"));
      goto out;
    }

  json_object = json_node_get_object (json_parser_get_root (parser));
  id = g_strdup (json_object_get_string_member (json_object, "id_str"));
  if (id == NULL)
    {
      goa_warning ("Did not find id_str in JSON data");
      g_set_error (error,
                   GOA_ERROR,
                   GOA_ERROR_FAILED,
                   _("Could not parse response"));
      goto out;
    }
  presentation_identity = g_strdup (json_object_get_string_member (json_object, "screen_name"));
  if (presentation_identity == NULL)
    {
      goa_warning ("Did not find screen_name in JSON data");
      g_set_error (error,
                   GOA_ERROR,
                   GOA_ERROR_FAILED,
                   _("Could not parse response"));
      goto out;
    }

  ret = id;
  id = NULL;
  if (out_presentation_identity != NULL)
    {
      *out_presentation_identity = presentation_identity;
      presentation_identity = NULL;
    }

 out:
  g_clear_error (&identity_error);
  g_free (id);
  g_free (presentation_identity);
  if (call != NULL)
    g_object_unref (call);
  if (proxy != NULL)
    g_object_unref (proxy);
  return ret;
}
