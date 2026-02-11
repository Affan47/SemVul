json_value_set_string (JsonValue *value,
                       const gchar *v_str)
{
  g_return_if_fail (JSON_VALUE_IS_VALID (value));
  g_return_if_fail (JSON_VALUE_HOLDS_STRING (value));

  g_free (value->data.v_str);
  value->data.v_str = g_strdup (v_str);
}
