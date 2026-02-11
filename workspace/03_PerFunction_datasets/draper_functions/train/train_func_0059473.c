clutter_shader_set_is_enabled (ClutterShader *shader,
                               gboolean       enabled)
{
  ClutterShaderPrivate *priv;

  g_return_if_fail (CLUTTER_IS_SHADER (shader));

  priv = shader->priv;

  if (priv->is_enabled != enabled)
    {
      GError *error = NULL;
      gboolean res;

      res = clutter_shader_compile (shader, &error);
      if (!res)
        {
          g_warning ("Unable to bind the shader: %s",
                     error ? error->message : "unknown error");
          if (error)
            g_error_free (error);

          return;
        }

      priv->is_enabled = enabled;

      if (priv->is_enabled)
        cogl_program_use (priv->program);
      else
        cogl_program_use (COGL_INVALID_HANDLE);

      g_object_notify_by_pspec (G_OBJECT (shader), obj_props[PROP_ENABLED]);
    }
}
