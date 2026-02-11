validity_changed_account_prepared_cb (GObject *object,
    GAsyncResult *res,
    gpointer user_data)
{
  TpAccountManager *self = user_data;
  TpAccount *account = (TpAccount *) object;
  GError *error = NULL;

  if (!tp_proxy_prepare_finish (object, res, &error))
    {
      DEBUG ("Error preparing account: %s", error->message);
      g_clear_error (&error);
      goto OUT;
    }


  if (tp_account_is_valid (account) &&
      tp_proxy_get_invalidated (account) == NULL)
    {
      insert_account (self, account);
      g_signal_emit (self, signals[ACCOUNT_VALIDITY_CHANGED], 0,
          account, TRUE);
    }

OUT:
  g_object_unref (self);
}
