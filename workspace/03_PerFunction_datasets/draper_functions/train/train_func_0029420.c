mx_grid_real_add (ClutterContainer *container,
                  ClutterActor     *actor)
{
  MxGridPrivate *priv;
  MxGridActorData *data;

  g_return_if_fail (MX_IS_GRID (container));

  priv = MX_GRID (container)->priv;

  g_object_ref (actor);

  clutter_actor_set_parent (actor, CLUTTER_ACTOR (container));

  data = g_slice_alloc0 (sizeof (MxGridActorData));

  priv->list = g_list_append (priv->list, actor);
  g_hash_table_insert (priv->hash_table, actor, data);

  g_signal_emit_by_name (container, "actor-added", actor);

  clutter_actor_queue_relayout (CLUTTER_ACTOR (container));

  g_object_unref (actor);
}
