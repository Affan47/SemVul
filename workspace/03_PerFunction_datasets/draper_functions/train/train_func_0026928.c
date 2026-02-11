set_using_ntp_cb (GObject      *source,
                  GAsyncResult *res,
                  gpointer      user_data)
{
  CcDateTimePanel *self = user_data;
  GError *error;

  error = NULL;
  if (!timedate1_call_set_ntp_finish (self->priv->dtm,
                                      res,
                                      &error))
    {

      g_warning ("Could not set system to use NTP: %s", error->message);
      g_error_free (error);
    }
}
