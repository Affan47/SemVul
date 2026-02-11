gst_app_src_uri_set_uri (GstURIHandler * handler, const gchar * uri,
    GError ** error)
{
  GstAppSrc *appsrc = GST_APP_SRC (handler);

  g_free (appsrc->priv->uri);
  appsrc->priv->uri = uri ? g_strdup (uri) : NULL;

  return TRUE;
}
