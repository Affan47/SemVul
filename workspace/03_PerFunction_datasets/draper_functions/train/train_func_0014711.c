tpaw_account_settings_processed_password (GObject *source,
    GAsyncResult *result,
    gpointer user_data,
    gpointer finish_func)
{
  TpawAccountSettings *settings = TPAW_ACCOUNT_SETTINGS (user_data);
  GSimpleAsyncResult *r;
  GError *error = NULL;
  gboolean (*func) (TpAccount *source, GAsyncResult *result, GError **error) =
    finish_func;

  g_free (settings->priv->password_original);
  settings->priv->password_original = g_strdup (settings->priv->password);

  if (!func (TP_ACCOUNT (source), result, &error))
    {
      g_simple_async_result_set_from_error (settings->priv->apply_result,
          error);
      g_error_free (error);
    }

  tpaw_account_settings_discard_changes (settings);

  r = settings->priv->apply_result;
  settings->priv->apply_result = NULL;

  g_simple_async_result_complete (r);
  g_object_unref (r);
}
