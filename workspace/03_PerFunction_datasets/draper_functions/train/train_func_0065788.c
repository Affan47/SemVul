gst_audio_clock_get_time (GstClock * clock)
{
  GstAudioClock *aclock;
  GstClockTime result;

  aclock = GST_AUDIO_CLOCK_CAST (clock);

  result = aclock->func (clock, aclock->user_data);
  if (result == GST_CLOCK_TIME_NONE) {
    GST_DEBUG_OBJECT (clock, "no time, reuse last");
    result = aclock->last_time - aclock->abidata.ABI.time_offset;
  }

  GST_DEBUG_OBJECT (clock,
      "result %" GST_TIME_FORMAT ", last_time %" GST_TIME_FORMAT,
      GST_TIME_ARGS (result), GST_TIME_ARGS (aclock->last_time));

  return result;
}
