terminal_profile_get_property_string (TerminalProfile *profile,
                                      const char *prop_name)
{
  const GValue *value;

  value = get_prop_value_from_prop_name (profile, prop_name);
  g_return_val_if_fail (value != NULL && G_VALUE_HOLDS_STRING (value), NULL);
  if (!value || !G_VALUE_HOLDS_STRING (value))
    return NULL;

  return g_value_get_string (value);
}
