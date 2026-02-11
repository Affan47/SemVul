fs_rtp_special_sources_destroy (GList *current_extra_sources)
{

  while (current_extra_sources)
  {
    FsRtpSpecialSource *self = current_extra_sources->data;

    self->priv->stopped_callback = NULL;
    g_object_unref (self);
    current_extra_sources = g_list_remove (current_extra_sources, self);
  }

  return NULL;
}
