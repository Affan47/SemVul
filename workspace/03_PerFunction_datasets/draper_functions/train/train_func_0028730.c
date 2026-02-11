mx_offscreen_set_accumulation_enabled (MxOffscreen *offscreen,
                                       gboolean     enable)
{
  MxOffscreenPrivate *priv;

  g_return_if_fail (MX_IS_OFFSCREEN (offscreen));

  priv = offscreen->priv;
  if (priv->acc_enabled != enable)
    {
      CoglHandle material =
        clutter_texture_get_cogl_material (CLUTTER_TEXTURE (offscreen));

      priv->acc_enabled = enable;

      if (enable)
        {
          CoglColor blend_color;

          GError *error = NULL;

          priv->acc_material = cogl_material_new ();


          cogl_color_set_from_4ub (&blend_color, 128, 128, 128, 128);
          cogl_material_set_blend_constant (material, &blend_color);

          if (!cogl_material_set_blend (material,
                                        "RGBA=ADD(SRC_COLOR*(CONSTANT[A]),"
                                                 "DST_COLOR*(1-CONSTANT[A]))",
                                        &error))
            {
              g_warning (G_STRLOC ": Error setting blend string: %s",
                         error->message);
              g_error_free (error);
            }
        }
      else
        {
          cogl_handle_unref (priv->acc_material);
          priv->acc_material = NULL;

          if (priv->acc_fbo)
            {
              cogl_handle_unref (priv->acc_fbo);
              priv->acc_fbo = NULL;
            }


          cogl_material_set_blend (material,
                                   "RGBA=ADD(SRC_COLOR,"
                                   "DST_COLOR*(1-SRC_COLOR[A]))",
                                   NULL);
        }

      g_object_notify (G_OBJECT (offscreen), "accumulation-enabled");
    }
}
