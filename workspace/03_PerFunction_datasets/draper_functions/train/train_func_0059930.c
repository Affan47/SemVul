gst_play_sink_get_av_offset (GstPlaySink * playsink)
{
  gint64 result;

  GST_PLAY_SINK_LOCK (playsink);
  result = playsink->av_offset;
  GST_PLAY_SINK_UNLOCK (playsink);

  return result;
}
