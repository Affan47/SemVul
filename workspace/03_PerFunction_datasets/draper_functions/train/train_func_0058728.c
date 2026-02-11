update_fbo (ClutterEffect *effect, int fbo_width, int fbo_height)
{
  ClutterOffscreenEffect *self = CLUTTER_OFFSCREEN_EFFECT (effect);
  ClutterOffscreenEffectPrivate *priv = self->priv;

  priv->stage = clutter_actor_get_stage (priv->actor);
  if (priv->stage == NULL)
    {
      CLUTTER_NOTE (MISC, "The actor '%s' is not part of a stage",
                    clutter_actor_get_name (priv->actor) == NULL
                      ? G_OBJECT_TYPE_NAME (priv->actor)
                      : clutter_actor_get_name (priv->actor));
      return FALSE;
    }

  if (priv->fbo_width == fbo_width &&
      priv->fbo_height == fbo_height &&
      priv->offscreen != NULL)
    return TRUE;

  if (priv->target == NULL)
    {
      CoglContext *ctx =
        clutter_backend_get_cogl_context (clutter_get_default_backend ());

      priv->target = cogl_pipeline_new (ctx);


      cogl_pipeline_set_layer_filters (priv->target,
                                       0,
                                       COGL_PIPELINE_FILTER_NEAREST,
                                       COGL_PIPELINE_FILTER_NEAREST);
    }

  if (priv->texture != NULL)
    {
      cogl_handle_unref (priv->texture);
      priv->texture = NULL;
    }

  priv->texture =
    clutter_offscreen_effect_create_texture (self, fbo_width, fbo_height);
  if (priv->texture == NULL)
    return FALSE;

  cogl_pipeline_set_layer_texture (priv->target, 0, priv->texture);

  priv->fbo_width = fbo_width;
  priv->fbo_height = fbo_height;

  if (priv->offscreen != NULL)
    cogl_handle_unref (priv->offscreen);

  priv->offscreen = cogl_offscreen_new_to_texture (priv->texture);
  if (priv->offscreen == NULL)
    {
      g_warning ("%s: Unable to create an Offscreen buffer", G_STRLOC);

      cogl_handle_unref (priv->target);
      priv->target = NULL;

      priv->fbo_width = 0;
      priv->fbo_height = 0;

      return FALSE;
    }

  return TRUE;
}
