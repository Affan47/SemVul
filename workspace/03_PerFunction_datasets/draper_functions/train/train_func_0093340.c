callback_parse_optional (const gchar *option_name, const gchar *value,
		 gpointer data, GError **error)
{
  callback_test_optional_boolean = TRUE;
  if (value)
    callback_test_optional_string = g_strdup (value);
  else
    callback_test_optional_string = NULL;
  return TRUE;
}
