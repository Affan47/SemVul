g_string_append_len (GString	 *string,
                     const gchar *val,
                     gssize       len)
{
  g_return_val_if_fail (string != NULL, NULL);
  g_return_val_if_fail (val != NULL, string);

  return g_string_insert_len (string, -1, val, len);
}
