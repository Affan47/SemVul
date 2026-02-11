tp_text_mixin_set_rescued (GObject *obj)
{
  TpTextMixin *mixin = TP_TEXT_MIXIN (obj);
  GList *cur;

  for (cur = g_queue_peek_head_link (mixin->priv->pending);
       cur != NULL;
       cur = cur->next)
    {
      _PendingMessage *msg = cur->data;

      msg->flags |= TP_CHANNEL_TEXT_MESSAGE_FLAG_RESCUED;
    }
}
