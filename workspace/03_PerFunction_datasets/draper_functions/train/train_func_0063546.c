empathy_server_sasl_handler_set_password_cb (GObject *source,
    GAsyncResult *result,
    gpointer user_data)
{
  GError *error = NULL;

  if (!empathy_keyring_set_account_password_finish (TP_ACCOUNT (source), result,
          &error))
    {
      DEBUG ("Failed to set password: %s", error->message);
      g_clear_error (&error);
    }
  else
    {
      DEBUG ("Password set successfully.");
    }
}
