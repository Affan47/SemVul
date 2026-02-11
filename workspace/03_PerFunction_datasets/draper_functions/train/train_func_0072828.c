st_scroll_view_vfade_set_offset (StScrollViewFade *self,
                                 float fade_offset)
{
  if (self->vfade_offset == fade_offset)
    return;

  g_object_freeze_notify (G_OBJECT (self));

  self->vfade_offset = fade_offset;

  if (self->actor != NULL)
    clutter_actor_queue_redraw (self->actor);

  g_object_notify (G_OBJECT (self), "vfade-offset");
  g_object_thaw_notify (G_OBJECT (self));
}
