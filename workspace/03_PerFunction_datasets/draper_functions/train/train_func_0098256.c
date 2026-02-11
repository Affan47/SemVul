tp_base_channel_reopened_with_requested (TpBaseChannel *chan,
    gboolean requested,
    TpHandle initiator)
{
  TpBaseChannelPrivate *priv = chan->priv;


  g_object_ref (chan);

  if (priv->initiator != initiator)
    priv->initiator = initiator;

  priv->requested = requested;
  priv->respawning = TRUE;

  tp_svc_channel_emit_closed (chan);

  if (!priv->registered)
    tp_base_channel_register (chan);

  g_object_unref (chan);
}
