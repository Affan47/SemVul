gst_rmdemux_descramble_audio (GstRMDemux * rmdemux, GstRMDemuxStream * stream)
{
  GstFlowReturn ret = GST_FLOW_ERROR;
  GstBuffer *outbuf;
  GstMapInfo outmap;
  guint packet_size = stream->packet_size;
  guint height = stream->subpackets->len;
  guint leaf_size = stream->leaf_size;
  guint p, x;

  g_assert (stream->height == height);

  GST_LOG ("packet_size = %u, leaf_size = %u, height= %u", packet_size,
      leaf_size, height);

  outbuf = gst_buffer_new_and_alloc (height * packet_size);
  gst_buffer_map (outbuf, &outmap, GST_MAP_WRITE);

  for (p = 0; p < height; ++p) {
    GstBuffer *b = g_ptr_array_index (stream->subpackets, p);
    GstMapInfo map;

    gst_buffer_map (b, &map, GST_MAP_READ);

    if (p == 0) {
      GST_BUFFER_PTS (outbuf) = GST_BUFFER_PTS (b);
      GST_BUFFER_DTS (outbuf) = GST_BUFFER_DTS (b);
    }

    for (x = 0; x < packet_size / leaf_size; ++x) {
      guint idx;

      idx = height * x + ((height + 1) / 2) * (p % 2) + (p / 2);


      memcpy (outmap.data + leaf_size * idx, map.data + leaf_size * x,
          leaf_size);
    }
    gst_buffer_unmap (b, &map);
  }
  gst_buffer_unmap (outbuf, &outmap);


  for (p = 0; p < height; ++p) {
    GstBuffer *subbuf;

    subbuf =
        gst_buffer_copy_region (outbuf, GST_BUFFER_COPY_ALL, p * packet_size,
        packet_size);

    GST_LOG_OBJECT (rmdemux, "pushing buffer dts %" GST_TIME_FORMAT ", pts %"
        GST_TIME_FORMAT, GST_TIME_ARGS (GST_BUFFER_DTS (subbuf)),
        GST_TIME_ARGS (GST_BUFFER_PTS (subbuf)));

    if (stream->discont) {
      GST_BUFFER_FLAG_SET (subbuf, GST_BUFFER_FLAG_DISCONT);
      stream->discont = FALSE;
    }

    ret = gst_pad_push (stream->pad, subbuf);
    if (ret != GST_FLOW_OK)
      break;
  }

  gst_buffer_unref (outbuf);

  gst_rmdemux_stream_clear_cached_subpackets (rmdemux, stream);

  return ret;
}
