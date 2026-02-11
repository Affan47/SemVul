new_packet_m2ts (MpegTsMux * mux, guint8 * data, guint len, gint64 new_pcr)
{
  GstBuffer *buf, *out_buf;
  GstFlowReturn ret;
  int chunk_bytes;

  GST_LOG_OBJECT (mux, "Have buffer with new_pcr=%" G_GINT64_FORMAT " size %d",
      new_pcr, len);

  buf = gst_buffer_new_and_alloc (M2TS_PACKET_LENGTH);
  if (G_UNLIKELY (buf == NULL)) {
    GST_ELEMENT_ERROR (mux, STREAM, MUX,
        ("Failed allocating output buffer"), (NULL));
    mux->last_flow_ret = GST_FLOW_ERROR;
    return FALSE;
  }


  memcpy (GST_BUFFER_DATA (buf) + 4, data, len);

  new_packet_common_init (mux, buf, data, len);

  if (new_pcr < 0) {


    GST_LOG_OBJECT (mux, "Accumulating non-PCR packet");
    gst_adapter_push (mux->adapter, buf);
    return TRUE;
  }

  chunk_bytes = gst_adapter_available (mux->adapter);


  if (mux->first_pcr) {


    gst_adapter_clear (mux->adapter);

    if (chunk_bytes) {
      GST_ELEMENT_WARNING (mux, STREAM, MUX,
          ("Discarding %d bytes from stream preceding first PCR",
              chunk_bytes / M2TS_PACKET_LENGTH * NORMAL_TS_PACKET_LENGTH),
          (NULL));
      chunk_bytes = 0;
    }
    mux->first_pcr = FALSE;
  }

  if (chunk_bytes) {


    guint64 pcr_bytes = M2TS_PACKET_LENGTH, ts_rate;


    chunk_bytes += M2TS_PACKET_LENGTH;


    ts_rate = gst_util_uint64_scale (chunk_bytes, CLOCK_FREQ_SCR,
        (new_pcr - mux->previous_pcr));
    GST_LOG_OBJECT (mux, "Processing pending packets with ts_rate %"
        G_GUINT64_FORMAT, ts_rate);

    while (1) {
      guint64 cur_pcr;


      cur_pcr = (mux->previous_pcr +
          gst_util_uint64_scale (pcr_bytes, CLOCK_FREQ_SCR, ts_rate));

      out_buf = gst_adapter_take_buffer (mux->adapter, M2TS_PACKET_LENGTH);
      if (G_UNLIKELY (!out_buf))
        break;
      gst_buffer_set_caps (out_buf, GST_PAD_CAPS (mux->srcpad));
      GST_BUFFER_TIMESTAMP (out_buf) = MPEG_SYS_TIME_TO_GSTTIME (cur_pcr);


      GST_WRITE_UINT32_BE (GST_BUFFER_DATA (out_buf), cur_pcr & 0x3FFFFFFF);

      GST_LOG_OBJECT (mux, "Outputting a packet of length %d PCR %"
          G_GUINT64_FORMAT, M2TS_PACKET_LENGTH, cur_pcr);
      ret = gst_pad_push (mux->srcpad, out_buf);
      if (G_UNLIKELY (ret != GST_FLOW_OK)) {
        mux->last_flow_ret = ret;
        return FALSE;
      }
      pcr_bytes += M2TS_PACKET_LENGTH;
    }
  }


  GST_WRITE_UINT32_BE (GST_BUFFER_DATA (buf), new_pcr & 0x3FFFFFFF);
  GST_BUFFER_TIMESTAMP (buf) = MPEG_SYS_TIME_TO_GSTTIME (new_pcr);

  GST_LOG_OBJECT (mux, "Outputting a packet of length %d PCR %"
      G_GUINT64_FORMAT, M2TS_PACKET_LENGTH, new_pcr);
  ret = gst_pad_push (mux->srcpad, buf);
  if (G_UNLIKELY (ret != GST_FLOW_OK)) {
    mux->last_flow_ret = ret;
    return FALSE;
  }

  mux->previous_pcr = new_pcr;

  return TRUE;
}
