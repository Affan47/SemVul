gdict_client_context_force_disconnect (GdictClientContext *context)
{
  GdictClientContextPrivate *priv = context->priv;

  if (priv->timeout_id)
    {
      g_source_remove (priv->timeout_id);
      priv->timeout_id = 0;
    }

  if (priv->source_id)
    {
      g_source_remove (priv->source_id);
      priv->source_id = 0;
    }

  if (priv->channel)
    {
      g_io_channel_shutdown (priv->channel, TRUE, NULL);
      g_io_channel_unref (priv->channel);

      priv->channel = NULL;
    }

  if (priv->command)
    {
      gdict_command_free (priv->command);
      priv->command = NULL;
    }

  clear_command_queue (context);
}
