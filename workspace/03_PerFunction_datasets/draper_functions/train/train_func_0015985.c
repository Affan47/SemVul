fsp_parser_get_access_token             (FspParser   *self,
                                         const gchar *buffer,
                                         gulong       buf_size,
                                         GError     **error)
{
  FspDataAuthToken *auth_token = NULL;
  gchar *response_str = NULL;
  gchar **response_array = NULL;
  gint i = 0;

  g_return_val_if_fail (FSP_IS_PARSER (self), NULL);
  g_return_val_if_fail (buffer != NULL, NULL);


  auth_token = FSP_DATA_AUTH_TOKEN (fsp_data_new (FSP_AUTH_TOKEN));
  response_str = g_strndup (buffer, buf_size);
  response_array = g_strsplit (response_str, "&", -1);
  g_free (response_str);

  for (i = 0; response_array[i]; i++)
    {
      if (g_str_has_prefix (response_array[i], "fullname="))
        auth_token->fullname = soup_uri_decode (&response_array[i][9]);

      if (g_str_has_prefix (response_array[i], "username="))
        auth_token->username = soup_uri_decode (&response_array[i][9]);

      if (g_str_has_prefix (response_array[i], "user_nsid="))
        auth_token->nsid = soup_uri_decode (&response_array[i][10]);

      if (g_str_has_prefix (response_array[i], "oauth_token="))
        auth_token->token = g_strdup (&response_array[i][12]);

      if (g_str_has_prefix (response_array[i], "oauth_token_secret="))
        auth_token->token_secret = g_strdup (&response_array[i][19]);
    }
  g_strfreev (response_array);


  if (!auth_token->token || !auth_token->token_secret)
    {
      GError *err = NULL;
      err = g_error_new (FSP_ERROR, FSP_ERROR_OAUTH_UNKNOWN_ERROR,
                         "An unknown error happened getting a permanent token");


      if (err != NULL)
        g_propagate_error (error, err);
    }


  return auth_token;
}
