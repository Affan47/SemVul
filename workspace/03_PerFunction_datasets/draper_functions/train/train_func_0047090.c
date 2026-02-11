fs_rtp_conference_dispose (GObject * object)
{
  FsRtpConference *self = FS_RTP_CONFERENCE (object);
  GList *item;

  if (self->priv->disposed)
    return;

  if (self->gstrtpbin) {
    gst_object_unref (self->gstrtpbin);
    self->gstrtpbin = NULL;
  }

  for (item = g_list_first (self->priv->sessions);
       item;
       item = g_list_next (item))
    g_object_weak_unref (G_OBJECT (item->data), _remove_session, self);
  g_list_free (self->priv->sessions);
  self->priv->sessions = NULL;
  self->priv->sessions_cookie++;

  for (item = g_list_first (self->priv->participants);
       item;
       item = g_list_next (item))
    g_object_weak_unref (G_OBJECT (item->data), _remove_participant, self);
  g_list_free (self->priv->participants);
  self->priv->participants = NULL;

  self->priv->disposed = TRUE;

  G_OBJECT_CLASS (parent_class)->dispose (object);
}
