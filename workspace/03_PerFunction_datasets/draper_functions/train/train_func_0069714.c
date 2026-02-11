_clutter_actor_queue_only_relayout (ClutterActor *self)
{
  ClutterActorPrivate *priv = self->priv;

  if (CLUTTER_ACTOR_IN_DESTRUCTION (self))
    return;

  if (priv->needs_width_request &&
      priv->needs_height_request &&
      priv->needs_allocation)
    return;

#if CLUTTER_ENABLE_DEBUG
  if (!CLUTTER_ACTOR_IS_TOPLEVEL (self) && CLUTTER_ACTOR_IN_RELAYOUT (self))
    {
      g_warning ("The actor '%s' is currently inside an allocation "
                 "cycle; calling clutter_actor_queue_relayout() is "
                 "not recommended",
                 _clutter_actor_get_debug_name (self));
    }
#endif

  _clutter_actor_queue_relayout_on_clones (self);

  g_signal_emit (self, actor_signals[QUEUE_RELAYOUT], 0);
}
