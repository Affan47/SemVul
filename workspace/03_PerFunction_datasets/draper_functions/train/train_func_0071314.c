gst_mxf_demux_sink_activate_mode (GstPad * sinkpad, GstObject * parent,
    GstPadMode mode, gboolean active)
{
  GstMXFDemux *demux;

  demux = GST_MXF_DEMUX (parent);

  if (mode == GST_PAD_MODE_PUSH) {
    demux->random_access = FALSE;
  } else {
    if (active) {
      demux->random_access = TRUE;
      return gst_pad_start_task (sinkpad, (GstTaskFunction) gst_mxf_demux_loop,
          sinkpad, NULL);
    } else {
      demux->random_access = FALSE;
      return gst_pad_stop_task (sinkpad);
    }
  }

  return TRUE;
}
