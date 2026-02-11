fs_rtp_session_set_codec_preferences (FsSession *session,
    GList *codec_preferences,
    GError **error)
{
  FsRtpSession *self = FS_RTP_SESSION (session);
  GList *old_codec_prefs = NULL;
  GList *new_codec_prefs = NULL;
  gboolean ret;
  guint current_generation;

  if (fs_rtp_session_has_disposed_enter (self, error))
    return FALSE;

  new_codec_prefs = fs_codec_list_copy (codec_preferences);

  new_codec_prefs =
    validate_codecs_configuration (
        self->priv->media_type, self->priv->blueprints,
        new_codec_prefs);

  if (new_codec_prefs == NULL)
    GST_DEBUG ("None of the new codec preferences passed are usable,"
        " this will restore the original list of detected codecs");

  FS_RTP_SESSION_LOCK (self);
  old_codec_prefs = self->priv->codec_preferences;
  self->priv->codec_preferences = new_codec_prefs;
  current_generation = self->priv->codec_preferences_generation;
  self->priv->codec_preferences_generation++;
  FS_RTP_SESSION_UNLOCK (self);

  ret = fs_rtp_session_update_codecs (self, NULL, NULL, error);

  if (ret)
  {
    fs_codec_list_destroy (old_codec_prefs);

    g_object_notify ((GObject*) self, "codec-preferences");
  }
  else
  {
    FS_RTP_SESSION_LOCK (self);
    if (self->priv->codec_preferences_generation == current_generation)
    {
      fs_codec_list_destroy (self->priv->codec_preferences);
      self->priv->codec_preferences = old_codec_prefs;
      self->priv->codec_preferences_generation++;
    }
    else
    {
      fs_codec_list_destroy (old_codec_prefs);
    }
    FS_RTP_SESSION_UNLOCK (self);
    GST_WARNING ("Invalid new codec preferences");
  }

  fs_rtp_session_has_disposed_exit (self);
  return ret;
}
