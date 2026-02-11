gst_apexsink_init (GstApExSink * apexsink, GstApExSinkClass * g_class)
{
  GstMixerTrack *track = NULL;

  track = g_object_new (GST_TYPE_MIXER_TRACK, NULL);
  track->label = g_strdup ("Airport Express");
  track->num_channels = GST_APEX_RAOP_CHANNELS;
  track->min_volume = 0;
  track->max_volume = 100;
  track->flags = GST_MIXER_TRACK_OUTPUT;

  apexsink->host = g_strdup (DEFAULT_APEX_HOST);
  apexsink->port = DEFAULT_APEX_PORT;
  apexsink->volume = CLAMP (DEFAULT_APEX_VOLUME * 75, 0, 100);
  apexsink->gst_apexraop = NULL;
  apexsink->tracks = g_list_append (apexsink->tracks, track);
  apexsink->clock = gst_system_clock_obtain ();
  apexsink->clock_id = NULL;

  GST_INFO_OBJECT (apexsink,
      "ApEx sink default initialization, target=\"%s\", port=\"%d\", volume=\"%d%%\"",
      apexsink->host, apexsink->port, apexsink->volume);
}
