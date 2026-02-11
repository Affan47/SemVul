clutter_actor_set_anchor_point_from_gravity (ClutterActor   *self,
					     ClutterGravity  gravity)
{
  g_return_if_fail (CLUTTER_IS_ACTOR (self));

  if (gravity == CLUTTER_GRAVITY_NONE)
    clutter_actor_set_anchor_point (self, 0, 0);
  else
    {
      GObject *obj = G_OBJECT (self);
      ClutterTransformInfo *info;

      g_object_freeze_notify (obj);

      info = _clutter_actor_get_transform_info (self);
      clutter_anchor_coord_set_gravity (&info->anchor, gravity);

      g_object_notify_by_pspec (obj, obj_props[PROP_ANCHOR_GRAVITY]);
      g_object_notify_by_pspec (obj, obj_props[PROP_ANCHOR_X]);
      g_object_notify_by_pspec (obj, obj_props[PROP_ANCHOR_Y]);

      self->priv->transform_valid = FALSE;

      clutter_actor_queue_redraw (self);

      g_object_thaw_notify (obj);
    }
}
