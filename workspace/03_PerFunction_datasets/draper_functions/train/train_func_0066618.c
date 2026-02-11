clutter_shader_effect_set_shader_source (ClutterShaderEffect *effect,
                                         const gchar         *source)
{
  ClutterShaderEffectPrivate *priv;

  g_return_val_if_fail (CLUTTER_IS_SHADER_EFFECT (effect), FALSE);
  g_return_val_if_fail (source != NULL && *source != '\0', FALSE);

  priv = effect->priv;

  if (priv->shader != COGL_INVALID_HANDLE)
    return TRUE;

  priv->shader = clutter_shader_effect_create_shader (effect);

  cogl_shader_source (priv->shader, source);

  CLUTTER_NOTE (SHADER, "Compiling shader effect");

  cogl_shader_compile (priv->shader);

  if (cogl_shader_is_compiled (priv->shader))
    {
      priv->program = cogl_create_program ();

      cogl_program_attach_shader (priv->program, priv->shader);

      cogl_program_link (priv->program);
    }
  else
    {
      gchar *log_buf = cogl_shader_get_info_log (priv->shader);

      g_warning (G_STRLOC ": Unable to compile the GLSL shader: %s", log_buf);
      g_free (log_buf);
    }

  return TRUE;
}
