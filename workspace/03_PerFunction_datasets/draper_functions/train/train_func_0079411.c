clutter_state_key_get_value (const ClutterStateKey *state_key,
                             GValue                *value)
{
  g_return_val_if_fail (state_key != NULL, FALSE);
  g_return_val_if_fail (value != NULL, FALSE);
  g_return_val_if_fail (G_VALUE_TYPE (value) != G_TYPE_INVALID, FALSE);

  if (!g_type_is_a (G_VALUE_TYPE (&state_key->value), G_VALUE_TYPE (value)))
    {
      if (g_value_type_compatible (G_VALUE_TYPE (&state_key->value),
                                   G_VALUE_TYPE (value)))
        {
          g_value_copy (&state_key->value, value);
          return TRUE;
        }

      if (g_value_type_transformable (G_VALUE_TYPE (&state_key->value),
                                      G_VALUE_TYPE (value)))
        {
          if (g_value_transform (&state_key->value, value))
            return TRUE;
        }

      g_warning ("%s: Unable to convert from %s to %s for the "
                 "property '%s' of object %s in the state key",
                 G_STRLOC,
                 g_type_name (G_VALUE_TYPE (&state_key->value)),
                 g_type_name (G_VALUE_TYPE (value)),
                 state_key->property_name,
                 G_OBJECT_TYPE_NAME (state_key->object));

      return FALSE;
    }
  else
    g_value_copy (&state_key->value, value);

  return TRUE;
}
