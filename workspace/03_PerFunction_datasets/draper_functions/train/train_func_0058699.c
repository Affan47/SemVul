gst_soup_http_client_sink_finalize (GObject * object)
{
  GstSoupHttpClientSink *souphttpsink = GST_SOUP_HTTP_CLIENT_SINK (object);


  g_free (souphttpsink->user_agent);
  g_free (souphttpsink->user_id);
  g_free (souphttpsink->user_pw);
  g_free (souphttpsink->proxy_id);
  g_free (souphttpsink->proxy_pw);
  if (souphttpsink->proxy)
    soup_uri_free (souphttpsink->proxy);
  g_free (souphttpsink->location);

  g_cond_free (souphttpsink->cond);
  g_mutex_free (souphttpsink->mutex);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
