gst_flv_demux_parse_header (GstFlvDemux * demux, GstBuffer * buffer)
{
  GstFlowReturn ret = GST_FLOW_OK;
  GstMapInfo map;

  g_return_val_if_fail (gst_buffer_get_size (buffer) >= 9, GST_FLOW_ERROR);

  gst_buffer_map (buffer, &map, GST_MAP_READ);


  if (map.data[0] == 'F' && map.data[1] == 'L' && map.data[2] == 'V') {
    GST_DEBUG_OBJECT (demux, "FLV header detected");
  } else {
    if (G_UNLIKELY (demux->strict)) {
      GST_WARNING_OBJECT (demux, "invalid header tag detected");
      ret = GST_FLOW_EOS;
      goto beach;
    }
  }

  if (map.data[3] == '1') {
    GST_DEBUG_OBJECT (demux, "FLV version 1 detected");
  } else {
    if (G_UNLIKELY (demux->strict)) {
      GST_WARNING_OBJECT (demux, "invalid header version detected");
      ret = GST_FLOW_EOS;
      goto beach;
    }

  }


  {
    guint8 flags = map.data[4];

    demux->has_video = demux->has_audio = FALSE;

    if (flags & 1) {
      GST_DEBUG_OBJECT (demux, "there is a video stream");
      demux->has_video = TRUE;
    }
    if (flags & 4) {
      GST_DEBUG_OBJECT (demux, "there is an audio stream");
      demux->has_audio = TRUE;
    }
  }


  gst_flv_demux_check_seekability (demux);


  demux->need_header = FALSE;

beach:
  gst_buffer_unmap (buffer, &map);
  return ret;
}
