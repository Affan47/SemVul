gst_ogg_demux_sink_activate_pull (GstPad * sinkpad, gboolean active)
{
  GstOggDemux *ogg;

  ogg = GST_OGG_DEMUX (GST_OBJECT_PARENT (sinkpad));

  if (active) {
    ogg->need_chains = TRUE;
    ogg->pullmode = TRUE;

    return gst_pad_start_task (sinkpad, (GstTaskFunction) gst_ogg_demux_loop,
        sinkpad);
  } else {
    return gst_pad_stop_task (sinkpad);
  }
}
