tp_base_media_call_content_dispose (GObject *object)
{
  TpBaseMediaCallContent *self = TP_BASE_MEDIA_CALL_CONTENT (object);

  g_assert (self->priv->current_offer == NULL);
  g_assert (self->priv->current_offer_result == NULL);
  g_assert (g_queue_is_empty (self->priv->outstanding_offers));

  tp_clear_pointer (&self->priv->local_media_descriptions, g_hash_table_unref);
  tp_clear_pointer (&self->priv->remote_media_descriptions, g_hash_table_unref);

  if (self->priv->tones_pause_timeout_id != 0)
    g_source_remove (self->priv->tones_pause_timeout_id);
  self->priv->tones_pause_timeout_id = 0;

  if (self->priv->channel_state_changed_id != 0)
    {
      TpBaseCallChannel *channel = _tp_base_call_content_get_channel (
          TP_BASE_CALL_CONTENT (self));

      g_signal_handler_disconnect (channel,
          self->priv->channel_state_changed_id);
      self->priv->channel_state_changed_id = 0;
    }

  if (G_OBJECT_CLASS (tp_base_media_call_content_parent_class)->dispose)
    G_OBJECT_CLASS (tp_base_media_call_content_parent_class)->dispose (object);
}
