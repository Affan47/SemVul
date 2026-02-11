player_set_user_agent (ClutterGstPlayer *player,
                       const gchar      *user_agent)
{
  ClutterGstPlayerPrivate *priv = PLAYER_GET_PRIVATE (player);
  GstElement *source;
  GParamSpec *pspec;

  if (user_agent == NULL)
    return;

  g_object_get (priv->pipeline, "source", &source, NULL);
  if (source == NULL)
    return;

  pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (source),
                                        "user-agent");
  if (pspec == NULL)
    return;

  CLUTTER_GST_NOTE (MEDIA, "setting user agent: %s", user_agent);

  g_object_set (source, "user-agent", user_agent, NULL);
}
