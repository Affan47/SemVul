mx_notebook_add (ClutterContainer *container,
                 ClutterActor     *actor)
{
  MxNotebookPrivate *priv = MX_NOTEBOOK (container)->priv;

  clutter_actor_set_parent (actor, CLUTTER_ACTOR (container));
  priv->children = g_list_append (priv->children, actor);

  if (!priv->current_page)
    {
      priv->current_page = actor;
      clutter_actor_set_opacity (actor, 0xff);
      g_object_notify (G_OBJECT (container), "current-page");
    }
  else
    clutter_actor_hide (actor);

  g_signal_emit_by_name (container, "actor-added", actor);
}
