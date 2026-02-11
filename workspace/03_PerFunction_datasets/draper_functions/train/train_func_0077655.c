tp_call_content_finalize (GObject *object)
{
  TpCallContent *self = (TpCallContent *) object;


  g_assert (self->priv->current_tones == NULL);
  g_assert (g_queue_is_empty (self->priv->tones_queue));
  g_queue_free (self->priv->tones_queue);

  G_OBJECT_CLASS (tp_call_content_parent_class)->finalize (object);
}
