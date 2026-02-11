user_dict (void)
{
  GError *error = NULL;
  SkkUserDict *dict = skk_user_dict_new ("user-dict.dat", "EUC-JP", &error);
  g_assert_no_error (error);
  gboolean read_only;

  g_assert (skk_dict_get_read_only (SKK_DICT (dict)) == FALSE);
  g_object_get (dict, "read-only", &read_only, NULL);
  g_assert (read_only == FALSE);
  g_object_unref (dict);
}
