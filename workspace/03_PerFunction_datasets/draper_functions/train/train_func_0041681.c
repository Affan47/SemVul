clutter_actor_set_size (ClutterActor *self,
			gfloat        width,
			gfloat        height)
{
  ClutterSize new_size;

  g_return_if_fail (CLUTTER_IS_ACTOR (self));

  clutter_size_init (&new_size, width, height);


  if (clutter_actor_get_easing_duration (self) == 0)
    {
      g_object_freeze_notify (G_OBJECT (self));

      clutter_actor_set_size_internal (self, &new_size);

      g_object_thaw_notify (G_OBJECT (self));

      return;
    }
  else
    {
      ClutterSize cur_size;

      clutter_size_init (&cur_size,
                         clutter_actor_get_width (self),
                         clutter_actor_get_height (self));

      _clutter_actor_create_transition (self,
                                        obj_props[PROP_SIZE],
                                        &cur_size,
                                        &new_size);
    }
}
