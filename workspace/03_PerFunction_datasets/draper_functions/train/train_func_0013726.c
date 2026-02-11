mx_offscreen_foreach (ClutterContainer *container,
                      ClutterCallback   callback,
                      gpointer          user_data)
{
  MxOffscreenPrivate *priv = MX_OFFSCREEN (container)->priv;

  if (priv->child &&
      (clutter_actor_get_parent (priv->child) == (ClutterActor *)container))
    callback (priv->child, user_data);
}
