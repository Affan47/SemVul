gst_mixer_track_dispose (GObject * object)
{
  GstMixerTrack *channel = GST_MIXER_TRACK (object);

  if (channel->label) {
    g_free (channel->label);
    channel->label = NULL;
  }

  if (parent_class->dispose)
    parent_class->dispose (object);
}
