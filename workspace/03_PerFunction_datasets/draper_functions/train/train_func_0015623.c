tp_base_media_call_stream_report_receiving_failure (
    TpSvcCallStreamInterfaceMedia *iface,
    TpCallStateChangeReason reason,
    const gchar *dbus_reason,
    const gchar *message,
    DBusGMethodInvocation *context)
{
  TpBaseMediaCallStream *self = TP_BASE_MEDIA_CALL_STREAM (iface);
  TpBaseMediaCallStreamClass *klass =
      TP_BASE_MEDIA_CALL_STREAM_GET_CLASS (self);
  TpStreamFlowState old_state = self->priv->receiving_state;
  TpBaseCallChannel *channel = _tp_base_call_stream_get_channel (
      TP_BASE_CALL_STREAM (self));
  gboolean was_held = FALSE;


  tp_intset_clear (self->priv->receiving_requests);

  if (self->priv->receiving_state == TP_STREAM_FLOW_STATE_STOPPED)
    goto done;

  self->priv->receiving_state = TP_STREAM_FLOW_STATE_STOPPED;
  self->priv->receiving_failure = TRUE;
  g_object_notify (G_OBJECT (self), "receiving-state");

  if (channel != NULL && TP_IS_BASE_MEDIA_CALL_CHANNEL (channel))
    was_held =
        _tp_base_media_call_channel_streams_receiving_state_changed (
            TP_BASE_MEDIA_CALL_CHANNEL (channel), FALSE);

  if (klass->report_receiving_failure != NULL && !was_held)
    klass->report_receiving_failure (self, old_state,
        reason, dbus_reason, message);

  tp_svc_call_stream_interface_media_emit_receiving_state_changed (self,
      self->priv->receiving_state);

  self->priv->receiving_failure = FALSE;

done:
  tp_svc_call_stream_interface_media_return_from_report_receiving_failure (
      context);
}
