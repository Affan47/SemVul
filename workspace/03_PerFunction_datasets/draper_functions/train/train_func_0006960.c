clutter_text_set_custom_property (ClutterScriptable *scriptable,
                                  ClutterScript     *script,
                                  const gchar       *name,
                                  const GValue      *value)
{
  if (strncmp (name, "font-description", 16) == 0)
    {
      g_assert (G_VALUE_HOLDS (value, G_TYPE_STRING));
      if (g_value_get_string (value) != NULL)
        clutter_text_set_font_name (CLUTTER_TEXT (scriptable),
                                    g_value_get_string (value));
    }
  else
    parent_scriptable_iface->set_custom_property (scriptable, script,
                                                  name,
                                                  value);
}
