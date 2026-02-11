grl_related_keys_get_string (GrlRelatedKeys *relkeys,
                             GrlKeyID key)
{
  const GValue *value = grl_related_keys_get (relkeys, key);

  if (!value || !G_VALUE_HOLDS_STRING (value)) {
    return NULL;
  } else {
    return g_value_get_string (value);
  }
}
