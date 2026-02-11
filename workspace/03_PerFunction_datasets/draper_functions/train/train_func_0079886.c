_parse_ges_element (GMarkupParseContext * context, const gchar * element_name,
    const gchar ** attribute_names, const gchar ** attribute_values,
    GESXmlFormatter * self, GError ** error)
{
  const gchar *version, *properties;
  guint api_version, min_version;

  gchar **split_version = NULL;

  if (g_strcmp0 (element_name, "ges")) {
    g_set_error (error, G_MARKUP_ERROR,
        G_MARKUP_ERROR_INVALID_CONTENT,
        "element '%s', Missing <ges> element'", element_name);
    return;
  }

  if (!g_markup_collect_attributes (element_name, attribute_names,
          attribute_values, error, G_MARKUP_COLLECT_STRING, "version", &version,
          COLLECT_STR_OPT, "properties", &properties,
          G_MARKUP_COLLECT_INVALID)) {
    return;
  }

  split_version = g_strsplit (version, ".", 2);
  if (split_version[1] == NULL)
    goto failed;

  errno = 0;
  api_version = g_ascii_strtoull (split_version[0], NULL, 10);
  if (errno || api_version != API_VERSION)
    goto stroull_failed;

  min_version = g_ascii_strtoull (split_version[1], NULL, 10);
  if (min_version > MINOR_VERSION)
    goto failed;

  _GET_PRIV (self)->ges_opened = TRUE;
  g_strfreev (split_version);
  return;

failed:
  g_set_error (error, G_MARKUP_ERROR,
      G_MARKUP_ERROR_INVALID_CONTENT,
      "element '%s', %s wrong version'", element_name, version);
  if (split_version)
    g_strfreev (split_version);

  return;

stroull_failed:
  GST_WARNING_OBJECT (self, "Error while strtoull: %s", g_strerror (errno));
  goto failed;
}
