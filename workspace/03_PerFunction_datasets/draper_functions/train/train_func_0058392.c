_clutter_stage_do_paint (ClutterStage                *stage,
                         const cairo_rectangle_int_t *clip)
{
  ClutterStagePrivate *priv = stage->priv;
  float clip_poly[8];
  float viewport[4];
  cairo_rectangle_int_t geom;
  int window_scale;

  if (priv->impl == NULL)
    return;

  _clutter_stage_window_get_geometry (priv->impl, &geom);
  window_scale = _clutter_stage_window_get_scale_factor (priv->impl);

  viewport[0] = priv->viewport[0] * window_scale;
  viewport[1] = priv->viewport[1] * window_scale;
  viewport[2] = priv->viewport[2] * window_scale;
  viewport[3] = priv->viewport[3] * window_scale;

  if (clip)
    {
      clip_poly[0] = MAX (clip->x * window_scale, 0);
      clip_poly[1] = MAX (clip->y * window_scale, 0);
      clip_poly[2] = MIN ((clip->x + clip->width) * window_scale, geom.width * window_scale);
      clip_poly[3] = clip_poly[1];
      clip_poly[4] = clip_poly[2];
      clip_poly[5] = MIN ((clip->y + clip->height) * window_scale, geom.height * window_scale);
      clip_poly[6] = clip_poly[0];
      clip_poly[7] = clip_poly[5];
    }
  else
    {
      clip_poly[0] = 0;
      clip_poly[1] = 0;
      clip_poly[2] = geom.width * window_scale;
      clip_poly[3] = 0;
      clip_poly[4] = geom.width * window_scale;
      clip_poly[5] = geom.height * window_scale;
      clip_poly[6] = 0;
      clip_poly[7] = geom.height * window_scale;
    }

  CLUTTER_NOTE (CLIPPING, "Setting stage clip too: "
                "x=%f, y=%f, width=%f, height=%f",
                clip_poly[0], clip_poly[1],
                clip_poly[2] - clip_poly[0],
                clip_poly[5] - clip_poly[1]);

  _cogl_util_get_eye_planes_for_screen_poly (clip_poly,
                                             4,
                                             viewport,
                                             &priv->projection,
                                             &priv->inverse_projection,
                                             priv->current_clip_planes);

  _clutter_stage_paint_volume_stack_free_all (stage);
  _clutter_stage_update_active_framebuffer (stage);
  clutter_actor_paint (CLUTTER_ACTOR (stage));

  clutter_stage_invoke_paint_callback (stage);
}
