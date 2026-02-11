clutter_actor_real_show (ClutterActor *self)
{
  ClutterActorPrivate *priv = self->priv;

  if (CLUTTER_ACTOR_IS_VISIBLE (self))
    return;

  CLUTTER_ACTOR_SET_FLAGS (self, CLUTTER_ACTOR_VISIBLE);


  clutter_actor_update_map_state (self, MAP_STATE_CHECK);


  if (priv->parent != NULL &&
      (!(priv->parent->flags & CLUTTER_ACTOR_NO_LAYOUT)))
    {


      priv->needs_width_request  = FALSE;
      priv->needs_height_request = FALSE;
      priv->needs_allocation     = FALSE;

      clutter_actor_queue_relayout (self);
    }
}
