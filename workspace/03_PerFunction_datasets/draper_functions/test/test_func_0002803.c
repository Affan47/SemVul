gst_tag_demux_get_upstream_size (GstTagDemux * tagdemux)
{
  gint64 len;


  if (tagdemux->priv->upstream_size > 0)
    return TRUE;

  if (!gst_pad_peer_query_duration (tagdemux->priv->sinkpad, GST_FORMAT_BYTES,
          &len) || len <= 0) {
    return FALSE;
  }

  tagdemux->priv->upstream_size = len;
  return TRUE;
}
