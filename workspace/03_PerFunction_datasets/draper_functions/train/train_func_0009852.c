maybe_send_tones (TpCallContent *self)
{
  if (self->priv->current_tones != NULL)
    return;

  if (g_queue_is_empty (self->priv->tones_queue))
    return;

  self->priv->current_tones = g_queue_pop_head (self->priv->tones_queue);


  if (g_cancellable_is_cancelled (self->priv->current_tones->cancellable))
    {
      GError e = { TP_ERROR, TP_ERROR_CANCELLED,
          "The DTMF tones were cancelled before it has started" };
      complete_sending_tones (self, &e);
      return;
    }

  DEBUG ("Emitting multiple tones: %s", self->priv->current_tones->tones);
  tp_cli_call_content_interface_dtmf_call_multiple_tones (self, -1,
      self->priv->current_tones->tones, multiple_tones_cb, NULL, NULL, NULL);
}
