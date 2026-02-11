gst_oss4_source_mixer_set_record (GstMixer * mixer, GstMixerTrack * track,
    gboolean record)
{
  GstOss4Source *oss;
  const gchar *cur_name;
  gint cur;

  g_return_if_fail (mixer != NULL);
  g_return_if_fail (track != NULL);
  g_return_if_fail (GST_IS_MIXER_TRACK (track));
  g_return_if_fail (GST_IS_OSS4_SOURCE (mixer));
  g_return_if_fail (GST_OSS4_SOURCE_IS_OPEN (mixer));

  oss = GST_OSS4_SOURCE (mixer);

  cur = gst_oss4_source_mixer_get_current_input (oss);


  if (!record && cur != GST_OSS4_SOURCE_INPUT (track)->route)
    goto done;


  if (record && cur == GST_OSS4_SOURCE_INPUT (track)->route)
    goto done;


  if (!record) {
    GST_WARNING_OBJECT (oss, "Can't un-select an input as such, only switch "
        "to a different input source");

  } else {
    int new_route = GST_OSS4_SOURCE_INPUT (track)->route;


    if (ioctl (oss->fd, SNDCTL_DSP_SET_RECSRC, &new_route) == -1) {
      GST_WARNING_OBJECT (oss, "Could not select input %d for recording: %s",
          new_route, g_strerror (errno));
    } else {
      cur = new_route;
    }
  }

done:

  cur_name = gst_oss4_source_mixer_update_record_flags (oss, cur);
  GST_DEBUG_OBJECT (oss, "active input route: %d (%s)", cur, cur_name);
}
