bvw_set_user_agent_on_element (BaconVideoWidget * bvw, GstElement * element)
{
  BaconVideoWidgetPrivate *priv = bvw->priv;
  const char *user_agent;

  if (g_object_class_find_property (G_OBJECT_GET_CLASS (element), "user-agent") == NULL)
    return;

  user_agent = priv->user_agent ? priv->user_agent : DEFAULT_USER_AGENT;
  GST_DEBUG ("Setting HTTP user-agent to '%s'", user_agent);
  g_object_set (element, "user-agent", user_agent, NULL);
}
