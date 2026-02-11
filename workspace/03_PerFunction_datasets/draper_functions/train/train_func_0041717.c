clutter_actor_unset_flags (ClutterActor      *self,
                           ClutterActorFlags  flags)
{
  ClutterActorFlags old_flags;
  GObject *obj;
  gboolean was_reactive_set, reactive_set;
  gboolean was_realized_set, realized_set;
  gboolean was_mapped_set, mapped_set;
  gboolean was_visible_set, visible_set;

  g_return_if_fail (CLUTTER_IS_ACTOR (self));

  obj = G_OBJECT (self);
  g_object_freeze_notify (obj);

  old_flags = self->flags;

  was_reactive_set = ((old_flags & CLUTTER_ACTOR_REACTIVE) != 0);
  was_realized_set = ((old_flags & CLUTTER_ACTOR_REALIZED) != 0);
  was_mapped_set   = ((old_flags & CLUTTER_ACTOR_MAPPED)   != 0);
  was_visible_set  = ((old_flags & CLUTTER_ACTOR_VISIBLE)  != 0);

  self->flags &= ~flags;

  if (self->flags == old_flags)
    return;

  reactive_set = ((self->flags & CLUTTER_ACTOR_REACTIVE) != 0);
  realized_set = ((self->flags & CLUTTER_ACTOR_REALIZED) != 0);
  mapped_set   = ((self->flags & CLUTTER_ACTOR_MAPPED)   != 0);
  visible_set  = ((self->flags & CLUTTER_ACTOR_VISIBLE)  != 0);

  if (reactive_set != was_reactive_set)
    g_object_notify_by_pspec (obj, obj_props[PROP_REACTIVE]);

  if (realized_set != was_realized_set)
    g_object_notify_by_pspec (obj, obj_props[PROP_REALIZED]);

  if (mapped_set != was_mapped_set)
    g_object_notify_by_pspec (obj, obj_props[PROP_MAPPED]);

  if (visible_set != was_visible_set)
    g_object_notify_by_pspec (obj, obj_props[PROP_VISIBLE]);

  g_object_thaw_notify (obj);
}
