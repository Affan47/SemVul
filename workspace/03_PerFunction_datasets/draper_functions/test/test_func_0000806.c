tp_message_mixin_implement_send_chat_state (GObject *object,
    TpMessageMixinSendChatStateImpl send_chat_state)
{
  TpMessageMixin *mixin = TP_MESSAGE_MIXIN (object);

  g_return_if_fail (mixin->priv->send_chat_state == NULL);

  mixin->priv->send_chat_state = send_chat_state;
}
