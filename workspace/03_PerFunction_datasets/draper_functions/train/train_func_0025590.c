clutter_actor_set_easing_delay (ClutterActor *self,
                                guint         msecs)
{
  ClutterAnimationInfo *info;

  g_return_if_fail (CLUTTER_IS_ACTOR (self));

  info = _clutter_actor_get_animation_info (self);

  if (info->cur_state == NULL)
    {
      g_warning ("You must call clutter_actor_save_easing_state() prior "
                 "to calling clutter_actor_set_easing_delay().");
      return;
    }

  if (info->cur_state->easing_delay != msecs)
    info->cur_state->easing_delay = msecs;
}
