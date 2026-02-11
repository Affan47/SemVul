set_boolean(GKeyFile *keyfile, const char *kb_name, const char *key, int *set)
{
  GError *err = NULL;
  gboolean b = g_key_file_get_boolean(keyfile, kb_name, key, &err);
  if (err) {
    g_error_free(err);
    err = NULL;
    b = g_key_file_get_boolean(keyfile, "default", key, &err);
    if (err) {
      g_error_free(err);
      err = NULL;
    } else {
      if (b) {
        *set = 1;
      } else {
        *set = 0;
      }
    }
  } else {
    if (b) {
      *set = 1;
    } else {
      *set = 0;
    }
  }
}
