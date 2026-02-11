tp_account_removed_by_us_cb (GObject      *object,
                             GAsyncResult *res,
                             gpointer      user_data)
{

  TpAccount *tp_account = TP_ACCOUNT (object);
  GError *error = NULL;

  if (!tp_account_remove_finish (tp_account, res, &error))
    {
      goa_error ("Error removing Telepathy account %s: %s (%s, %d)",
          get_id_from_tp_account (tp_account),
          error->message,
          g_quark_to_string (error->domain),
          error->code);
      g_error_free (error);
    }
}
