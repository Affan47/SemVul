clutter_scriptable_parse_custom_node (ClutterScriptable *scriptable,
                                      ClutterScript     *script,
                                      GValue            *value,
                                      const gchar       *name,
                                      JsonNode          *node)
{
  ClutterScriptableIface *iface;

  g_return_val_if_fail (CLUTTER_IS_SCRIPTABLE (scriptable), FALSE);
  g_return_val_if_fail (CLUTTER_IS_SCRIPT (script), FALSE);
  g_return_val_if_fail (name != NULL, FALSE);
  g_return_val_if_fail (node != NULL, FALSE);

  iface = CLUTTER_SCRIPTABLE_GET_IFACE (scriptable);
  if (iface->parse_custom_node)
    return iface->parse_custom_node (scriptable, script, value, name, node);

  return FALSE;
}
