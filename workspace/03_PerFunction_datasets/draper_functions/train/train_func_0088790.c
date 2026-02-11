cull_actor (ClutterActor *self, ClutterCullResult *result_out)
{
  ClutterActorPrivate *priv = self->priv;
  ClutterActor *stage;
  const ClutterPlane *stage_clip;

  if (!priv->last_paint_volume_valid)
    {
      CLUTTER_NOTE (CLIPPING, "Bail from cull_actor without culling (%s): "
                    "->last_paint_volume_valid == FALSE",
                    _clutter_actor_get_debug_name (self));
      return FALSE;
    }

  if (G_UNLIKELY (clutter_paint_debug_flags & CLUTTER_DEBUG_DISABLE_CULLING))
    return FALSE;

  stage = _clutter_actor_get_stage_internal (self);
  stage_clip = _clutter_stage_get_clip (CLUTTER_STAGE (stage));
  if (G_UNLIKELY (!stage_clip))
    {
      CLUTTER_NOTE (CLIPPING, "Bail from cull_actor without culling (%s): "
                    "No stage clip set",
                    _clutter_actor_get_debug_name (self));
      return FALSE;
    }

  if (cogl_get_draw_framebuffer () !=
      _clutter_stage_get_active_framebuffer (CLUTTER_STAGE (stage)))
    {
      CLUTTER_NOTE (CLIPPING, "Bail from cull_actor without culling (%s): "
                    "Current framebuffer doesn't correspond to stage",
                    _clutter_actor_get_debug_name (self));
      return FALSE;
    }

  *result_out =
    _clutter_paint_volume_cull (&priv->last_paint_volume, stage_clip);
  return TRUE;
}
