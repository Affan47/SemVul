handle_uri (BishoWindow *window, const char *s)
{
  SoupURI *uri = NULL;
  GHashTable *params = NULL;

  uri = soup_uri_new (s);
  if (strcmp (uri->scheme, "x-bisho") != 0) {
    soup_uri_free (uri);
    return;
  }

  if (uri->query)
    params = soup_form_decode (uri->query);
  else
    params = g_hash_table_new (NULL, NULL);

  bisho_frame_callback (BISHO_FRAME (window->frame), uri->path, params);

  g_hash_table_destroy (params);
  soup_uri_free (uri);
}
