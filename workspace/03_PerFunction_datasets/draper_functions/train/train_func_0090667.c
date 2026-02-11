clutter_script_add_states (ClutterScript *script,
                           const gchar   *name,
                           ClutterState  *state)
{
  g_return_if_fail (CLUTTER_IS_SCRIPT (script));
  g_return_if_fail (CLUTTER_IS_STATE (state));

  if (name == NULL || *name == '\0')
    name = "__clutter_script_default_state";

  g_hash_table_replace (script->priv->states,
                        g_strdup (name),
                        g_object_ref (state));
}
