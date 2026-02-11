hold_change_failed (TpBaseMediaCallChannel *self)
{
  TpBaseCallChannel *bcc = TP_BASE_CALL_CHANNEL (self);
  GList *l, *l2;

  if (self->priv->hold_state != TP_LOCAL_HOLD_STATE_PENDING_UNHOLD)
    return;

  set_hold_state (self, TP_LOCAL_HOLD_STATE_PENDING_HOLD,
      TP_LOCAL_HOLD_STATE_REASON_RESOURCE_NOT_AVAILABLE);

  for (l = tp_base_call_channel_get_contents (bcc); l != NULL; l = l->next)
    {
      for (l2 = tp_base_call_content_get_streams (l->data);
           l2 != NULL; l2 = l2->next)
        {
          TpBaseMediaCallStream *stream = TP_BASE_MEDIA_CALL_STREAM (l2->data);

          tp_base_media_call_stream_update_receiving_state (stream);
          tp_base_media_call_stream_update_sending_state (stream);
        }
    }


  update_hold_state (self);
}
