mx_container_remove_actor (ClutterContainer *container,
                           ClutterActor     *actor)
{
  MxTablePrivate *priv = MX_TABLE (container)->priv;
  gint rows, cols;

  GList *item = NULL;
  MxTableChild *meta;
  GList *l;

  item = g_list_find (priv->children, actor);

  if (item == NULL)
    {
      g_warning ("Widget of type '%s' is not a child of container of type '%s'",
                 g_type_name (G_OBJECT_TYPE (actor)),
                 g_type_name (G_OBJECT_TYPE (container)));
      return;
    }

  g_object_ref (actor);

  if ((ClutterActor *)priv->last_focus == actor)
    priv->last_focus = NULL;

  priv->children = g_list_delete_link (priv->children, item);
  clutter_actor_unparent (actor);


  rows = 0;
  cols = 0;
  for (l = priv->children; l; l = l->next)
    {
      ClutterActor *child = CLUTTER_ACTOR (l->data);
      meta = (MxTableChild *) clutter_container_get_child_meta (container,
                                                                  child);
      rows = MAX (rows, meta->row + meta->row_span);
      cols = MAX (cols, meta->col + meta->col_span);
    }
  priv->n_rows = rows;
  priv->n_cols = cols;

  clutter_actor_queue_relayout (CLUTTER_ACTOR (container));

  g_signal_emit_by_name (container, "actor-removed", actor);

  g_object_unref (actor);
}
