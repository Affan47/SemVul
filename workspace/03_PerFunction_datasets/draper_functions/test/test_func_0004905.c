example_call_channel_terminate (ExampleCallChannel *self,
    TpHandle actor,
    TpChannelGroupChangeReason reason,
    TpCallStateChangeReason call_reason,
    const gchar *error_name)
{
  TpBaseCallChannel *base = (TpBaseCallChannel *) self;
  TpCallState call_state = tp_base_call_channel_get_state (base);

  if (call_state != TP_CALL_STATE_ENDED)
    {
      GList *contents;

      example_call_channel_set_state (self,
          TP_CALL_STATE_ENDED, 0, actor,
          call_reason, error_name,
          NULL);


      tp_base_call_channel_remove_member (base, self->priv->handle,
          actor, call_reason, error_name, NULL);

      if (actor == tp_base_connection_get_self_handle (self->priv->conn))
        {
          const gchar *send_reason;


          switch (reason)
            {
            case TP_CHANNEL_GROUP_CHANGE_REASON_BUSY:
              send_reason = "<user-is-busy/>";
              break;

            case TP_CHANNEL_GROUP_CHANGE_REASON_NO_ANSWER:
              send_reason = "<no-answer/>";
              break;

            default:
              send_reason = "<call-terminated/>";
            }

          g_message ("SIGNALLING: send: Terminating call: %s", send_reason);
        }


      contents = tp_base_call_channel_get_contents (base);
      contents = g_list_copy (contents);
      for (; contents != NULL; contents = g_list_delete_link (contents, contents))
        {
          example_call_content_remove_stream (contents->data);
          tp_base_call_channel_remove_content (base, contents->data,
              0, call_reason, error_name, "");
        }
    }
}
