foo_new_shader_effect_get_static_source (ClutterShaderEffect *effect)
{
  static gboolean already_called = FALSE;


  g_assert (!already_called);

  already_called = TRUE;

  return g_strdup (new_shader_effect_source);
}
