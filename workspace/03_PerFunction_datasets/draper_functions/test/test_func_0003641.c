tp_call_channel_dispose (GObject *obj)
{
  TpCallChannel *self = (TpCallChannel *) obj;

  g_assert (self->priv->core_result == NULL);

  tp_clear_pointer (&self->priv->contents, g_ptr_array_unref);
  tp_clear_pointer (&self->priv->state_details, g_hash_table_unref);
  tp_clear_pointer (&self->priv->state_reason, _tp_call_state_reason_unref);
  tp_clear_pointer (&self->priv->members, g_hash_table_unref);
  tp_clear_pointer (&self->priv->initial_audio_name, g_free);
  tp_clear_pointer (&self->priv->initial_video_name, g_free);

  G_OBJECT_CLASS (tp_call_channel_parent_class)->dispose (obj);
}
