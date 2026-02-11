gst_flups_demux_reset (GstFluPSDemux * demux)
{

  gint i;
  GstEvent **p_ev;

  for (i = 0; i < GST_FLUPS_DEMUX_MAX_STREAMS; i++) {
    GstFluPSStream *stream = demux->streams[i];

    if (stream != NULL) {
      if (stream->pad)
        gst_element_remove_pad (GST_ELEMENT_CAST (demux), stream->pad);

      g_free (stream);
      demux->streams[i] = NULL;
    }
  }

  p_ev = &demux->lang_codes;

  gst_event_replace (p_ev, NULL);
  demux->scr_adjust = GSTTIME_TO_MPEGTIME (SCR_MUNGE);
  demux->have_group_id = FALSE;
  demux->group_id = G_MAXUINT;
}
