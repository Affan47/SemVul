pretend_disconnected (gpointer data)
{
  TpTestsSimpleConnection *self = TP_TESTS_SIMPLE_CONNECTION (data);


  g_hash_table_remove_all (self->priv->text_channels);
  g_clear_object (&self->priv->room_list_chan);

  tp_base_connection_finish_shutdown (TP_BASE_CONNECTION (data));
  self->priv->disconnect_source = 0;
  return FALSE;
}
