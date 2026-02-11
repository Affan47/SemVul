tp_tests_simple_normalize_contact (TpHandleRepoIface *repo,
                           const gchar *id,
                           gpointer context,
                           GError **error)
{
  if (id[0] == '\0')
    {
      g_set_error (error, TP_ERROR, TP_ERROR_INVALID_HANDLE,
          "ID must not be empty");
      return NULL;
    }

  if (strchr (id, ' ') != NULL)
    {
      g_set_error (error, TP_ERROR, TP_ERROR_INVALID_HANDLE,
          "ID must not contain spaces");
      return NULL;
    }

  return g_utf8_strdown (id, -1);
}
