example_call_stream_accept_proposed_direction (ExampleCallStream *self)
{
  TpBaseCallStream *base = (TpBaseCallStream *) self;
  TpSendingState state = tp_base_call_stream_get_local_sending_state (base);

  if (state != TP_SENDING_STATE_PENDING_SEND)
    return;

  tp_base_call_stream_update_local_sending_state (base,
      TP_SENDING_STATE_SENDING, 0, TP_CALL_STATE_CHANGE_REASON_UNKNOWN,
      "", "");
}
