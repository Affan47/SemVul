gst_rmdemux_handle_scrambled_packet (GstRMDemux * rmdemux,
    GstRMDemuxStream * stream, GstBuffer * buf, gboolean keyframe)
{
  GstFlowReturn ret;

  if (stream->subpackets == NULL)
    stream->subpackets = g_ptr_array_sized_new (stream->subpackets_needed);

  GST_LOG ("Got subpacket %u/%u, len=%" G_GSIZE_FORMAT ", key=%d",
      stream->subpackets->len + 1, stream->subpackets_needed,
      gst_buffer_get_size (buf), keyframe);

  if (keyframe && stream->subpackets->len > 0) {
    gst_rmdemux_stream_clear_cached_subpackets (rmdemux, stream);
  }

  g_ptr_array_add (stream->subpackets, buf);

  if (stream->subpackets->len < stream->subpackets_needed)
    return GST_FLOW_OK;

  g_assert (stream->subpackets->len >= 1);

  switch (stream->fourcc) {
    case GST_RM_AUD_DNET:
      ret = gst_rmdemux_descramble_dnet_audio (rmdemux, stream);
      break;
    case GST_RM_AUD_COOK:
    case GST_RM_AUD_ATRC:
      ret = gst_rmdemux_descramble_audio (rmdemux, stream);
      break;
    case GST_RM_AUD_RAAC:
    case GST_RM_AUD_RACP:
      ret = gst_rmdemux_descramble_mp4a_audio (rmdemux, stream);
      break;
    case GST_RM_AUD_SIPR:
      ret = gst_rmdemux_descramble_sipr_audio (rmdemux, stream);
      break;
    default:
      ret = GST_FLOW_ERROR;
      g_assert_not_reached ();
  }

  return ret;
}
