finalize (GObject *object)
{
  TpTestsTextChannelGroup *self = TP_TESTS_TEXT_CHANNEL_GROUP (object);

  tp_text_mixin_finalize (object);
  tp_group_mixin_finalize (object);

  tp_clear_pointer (&self->priv->password, g_free);

  ((GObjectClass *) tp_tests_text_channel_group_parent_class)->finalize (object);
}
