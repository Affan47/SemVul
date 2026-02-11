gst_apexsink_write (GstAudioSink * asink, gpointer data, guint length)
{
  guint written;
  GstApExSink *apexsink = (GstApExSink *) asink;

  if ((written =
          gst_apexraop_write (apexsink->gst_apexraop, data,
              length)) != length) {
    GST_INFO_OBJECT (apexsink,
        "WRITE : %d of %d bytes sent, skipping frame samples...", written,
        length);
  } else {
    GST_INFO_OBJECT (apexsink, "WRITE : %d bytes sent", length);


    apexsink->clock_id = gst_clock_new_single_shot_id (apexsink->clock,
        (GstClockTime) (gst_clock_get_time (apexsink->clock) +
            ((length * 1000000000.)
                / (GST_APEX_RAOP_BITRATE * GST_APEX_RAOP_BYTES_PER_SAMPLE))));
    gst_clock_id_wait (apexsink->clock_id, NULL);
    gst_clock_id_unref (apexsink->clock_id);
    apexsink->clock_id = NULL;
  }

  return length;
}
