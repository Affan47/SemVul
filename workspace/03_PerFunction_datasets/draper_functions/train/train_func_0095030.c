mx_texture_frame_set_parent_texture (MxTextureFrame *frame,
                                     ClutterTexture *texture)
{
  MxTextureFramePrivate *priv;
  gboolean was_visible;

  g_return_if_fail (MX_IS_TEXTURE_FRAME (frame));
  g_return_if_fail (texture == NULL || CLUTTER_IS_TEXTURE (texture));

  priv = frame->priv;

  was_visible = CLUTTER_ACTOR_IS_VISIBLE (frame);

  if (priv->parent_texture == texture)
    return;

  if (priv->parent_texture)
    {
      g_object_unref (priv->parent_texture);
      priv->parent_texture = NULL;

      if (was_visible)
        clutter_actor_hide (CLUTTER_ACTOR (frame));
    }

  if (texture)
    {
      CoglHandle cogl_material = COGL_INVALID_HANDLE;

      priv->parent_texture = g_object_ref_sink (texture);

      if (was_visible && CLUTTER_ACTOR_IS_VISIBLE (priv->parent_texture))
        clutter_actor_show (CLUTTER_ACTOR (frame));


      cogl_material = clutter_texture_get_cogl_material (priv->parent_texture);
      cogl_material_set_layer_wrap_mode (cogl_material, 0,
                                         COGL_MATERIAL_WRAP_MODE_REPEAT);


      cogl_material_set_layer_filters (cogl_material,
                                       0,
                                       COGL_MATERIAL_FILTER_NEAREST,
                                       COGL_MATERIAL_FILTER_NEAREST);


    }

  clutter_actor_queue_relayout (CLUTTER_ACTOR (frame));

  g_object_notify (G_OBJECT (frame), "parent-texture");
}
