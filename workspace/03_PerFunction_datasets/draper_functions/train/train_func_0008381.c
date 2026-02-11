clutter_group_real_actor_removed (ClutterContainer *container,
                                  ClutterActor     *actor)
{
  ClutterGroupPrivate *priv = CLUTTER_GROUP (container)->priv;


  if (g_list_find (priv->children, actor) == NULL)
    return;

  priv->children = g_list_remove (priv->children, actor);
}
