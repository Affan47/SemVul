goa_client_new_cb (GObject      *object,
                   GAsyncResult *result,
                   gpointer      user_data)
{
  GoaTpAccountLinker *self = user_data;
  GoaTpAccountLinkerPrivate *priv = self->priv;
  GError *error = NULL;

  priv->goa_client = goa_client_new_finish (result, &error);
  if (priv->goa_client == NULL)
    {
      goa_error ("Error connecting to GOA: %s", error->message);
      g_clear_error (&error);
      return;
    }

  goa_debug("GOA client ready");
  start_if_ready (self);
}
