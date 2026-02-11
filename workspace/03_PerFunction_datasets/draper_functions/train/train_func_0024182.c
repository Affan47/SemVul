clutter_actor_set_position_internal (ClutterActor       *self,
                                     const ClutterPoint *position)
{
  ClutterActorPrivate *priv = self->priv;
  ClutterLayoutInfo *linfo;
  ClutterActorBox old = { 0, };

  linfo = _clutter_actor_get_layout_info (self);

  if (priv->position_set &&
      clutter_point_equals (position, &linfo->fixed_pos))
    return;

  clutter_actor_store_old_geometry (self, &old);

  if (position != NULL)
    {
      linfo->fixed_pos = *position;
      clutter_actor_set_fixed_position_set (self, TRUE);
    }
  else
    clutter_actor_set_fixed_position_set (self, FALSE);

  clutter_actor_notify_if_geometry_changed (self, &old);

  clutter_actor_queue_relayout (self);
}
