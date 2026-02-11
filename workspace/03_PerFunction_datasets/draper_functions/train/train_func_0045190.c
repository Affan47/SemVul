clutter_alpha_parse_custom_node (ClutterScriptable *scriptable,
                                 ClutterScript     *script,
                                 GValue            *value,
                                 const gchar       *name,
                                 JsonNode          *node)
{
  if (strncmp (name, "function", 8) == 0)
    {
      const gchar *func_name = json_node_get_string (node);

      g_value_init (value, G_TYPE_POINTER);
      g_value_set_pointer (value, resolve_alpha_func (func_name));

      return TRUE;
    }


  if (strncmp (name, "mode", 4) == 0)
    {
      gulong mode;

      mode = _clutter_script_resolve_animation_mode (node);

      g_value_init (value, G_TYPE_ULONG);
      g_value_set_ulong (value, mode);

      return TRUE;
    }

  return FALSE;
}
