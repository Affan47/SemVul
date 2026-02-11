evd_connection_socket_input_stream_drained (GInputStream *stream,
                                            gpointer      user_data)
{
  EvdConnection *self = EVD_CONNECTION (user_data);

  if (CLOSED (self))
    return;

  if (self->priv->delayed_close && ! self->priv->close_locked)
    {
      evd_connection_close_in_idle (self);
    }
  else
    {
      GError *error = NULL;

      self->priv->cond &= ~G_IO_IN;

      if (! evd_socket_watch_condition (self->priv->socket,
                                        ~self->priv->cond,
                                        &error))
        {

          g_warning ("Undandled error: watch socket condition error: %s", error->message);
          g_error_free (error);
        }
    }
}
