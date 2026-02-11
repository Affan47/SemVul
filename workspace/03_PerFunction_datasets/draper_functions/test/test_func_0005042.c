gnac_profiles_properties_is_valid_filename_chars(const gchar *chars)
{
  guint i, j;
  glong len = g_utf8_strlen(chars, -1);

  for (i = 0; i < len; i++) {
    for (j = 0; j < G_N_ELEMENTS(forbidden_chars); j++) {
      if (chars[i] == forbidden_chars[j]) {
        return FALSE;
      }
    }
  }

  return TRUE;
}
