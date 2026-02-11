entry_parsed_cb (TotemPlParser  *parser,
                 const char     *uri,
                 GHashTable     *metadata,
                 GrlMedia      **media)
{
  char *scheme;

  g_return_if_fail (*media != NULL);
  if (grl_media_get_url (*media) != NULL) {
    GRL_WARNING ("Was going to set media '%s' to URL '%s' but already has URL '%s'",
                 grl_media_get_id (*media),
                 uri,
                 grl_media_get_url (*media));
    return;
  }

  scheme = g_uri_parse_scheme (uri);
  if (scheme != NULL && !g_str_equal (scheme, "file"))
    grl_media_set_url (*media, uri);
  g_free (scheme);
}
