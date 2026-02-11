gst_audio_rate_reset (GstAudioRate * audiorate)
{
  audiorate->next_offset = -1;
  audiorate->next_ts = -1;
  audiorate->discont = TRUE;
  gst_segment_init (&audiorate->sink_segment, GST_FORMAT_UNDEFINED);
  gst_segment_init (&audiorate->src_segment, GST_FORMAT_TIME);

  GST_DEBUG_OBJECT (audiorate, "handle reset");
}
