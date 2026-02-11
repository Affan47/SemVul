gst_flups_demux_change_state (GstElement * element, GstStateChange transition)
{
  GstFluPSDemux *demux = GST_FLUPS_DEMUX (element);
  GstStateChangeReturn result;

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      demux->adapter = gst_adapter_new ();
      demux->rev_adapter = gst_adapter_new ();
      demux->adapter_offset = G_MAXUINT64;
      gst_pes_filter_init (&demux->filter, demux->adapter,
          &demux->adapter_offset);
      gst_pes_filter_set_callbacks (&demux->filter,
          (GstPESFilterData) gst_flups_demux_data_cb,
          (GstPESFilterResync) gst_flups_demux_resync_cb, demux);
      demux->filter.gather_pes = TRUE;
      demux->first_scr = G_MAXUINT64;
      demux->bytes_since_scr = 0;
      demux->current_scr = G_MAXUINT64;
      demux->base_time = G_MAXUINT64;
      demux->scr_rate_n = G_MAXUINT64;
      demux->scr_rate_d = G_MAXUINT64;
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      demux->current_scr = G_MAXUINT64;
      demux->mux_rate = G_MAXUINT64;
      demux->next_pts = G_MAXUINT64;
      demux->next_dts = G_MAXUINT64;
      demux->first_scr = G_MAXUINT64;
      demux->bytes_since_scr = 0;
      demux->base_time = G_MAXUINT64;
      demux->scr_rate_n = G_MAXUINT64;
      demux->scr_rate_d = G_MAXUINT64;
      demux->need_no_more_pads = TRUE;

      gst_flups_demux_reset_psm (demux);
      gst_segment_init (&demux->sink_segment, GST_FORMAT_UNDEFINED);
      gst_segment_init (&demux->src_segment, GST_FORMAT_TIME);
      gst_flups_demux_flush (demux);
      break;
    default:
      break;
  }

  result = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_flups_demux_reset (demux);
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      gst_pes_filter_uninit (&demux->filter);
      g_object_unref (demux->adapter);
      demux->adapter = NULL;
      g_object_unref (demux->rev_adapter);
      demux->rev_adapter = NULL;
      break;
    default:
      break;
  }

  return result;
}
