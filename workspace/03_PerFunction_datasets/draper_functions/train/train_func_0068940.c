mpegtsmux_process_codec_data_h264 (MpegTsPadData * data, MpegTsMux * mux)
{
  PrivDataH264 *h264_data;
  gboolean ret = FALSE;


  if (G_UNLIKELY (!data->prepare_data)) {
    data->prepare_data = g_new0 (PrivDataH264, 1);
    h264_data = (PrivDataH264 *) data->prepare_data;
    h264_data->last_resync_ts = GST_CLOCK_TIME_NONE;
  }

  h264_data = (PrivDataH264 *) data->prepare_data;


  if (h264_data->last_codec_data != data->codec_data) {
    if (h264_data->cached_es) {
      gst_buffer_unref (h264_data->cached_es);
      h264_data->cached_es = NULL;
    }
    ret = TRUE;
  }


  if (G_UNLIKELY (!h264_data->cached_es)) {
    gint offset = 4, i = 0, nb_sps = 0, nb_pps = 0;
    gsize out_offset = 0;
    guint8 startcode[4] = { 0x00, 0x00, 0x00, 0x01 };
    h264_data->last_codec_data = data->codec_data;
    h264_data->cached_es =
        gst_buffer_new_and_alloc (GST_BUFFER_SIZE (data->codec_data) * 10);


    h264_data->nal_length_size =
        (GST_READ_UINT8 (GST_BUFFER_DATA (data->codec_data) + offset) & 0x03) +
        1;
    GST_LOG_OBJECT (mux, "NAL length will be coded on %u bytes",
        h264_data->nal_length_size);
    offset++;


    nb_sps =
        GST_READ_UINT8 (GST_BUFFER_DATA (data->codec_data) + offset) & 0x1f;
    GST_DEBUG_OBJECT (mux, "we have %d Sequence Parameter Set", nb_sps);
    offset++;


    for (i = 0; i < nb_sps; i++) {
      guint16 sps_size =
          GST_READ_UINT16_BE (GST_BUFFER_DATA (data->codec_data) + offset);

      GST_LOG_OBJECT (mux, "Sequence Parameter Set is %d bytes", sps_size);


      offset += 2;


      memcpy (GST_BUFFER_DATA (h264_data->cached_es) + out_offset,
          startcode, 4);
      out_offset += 4;

      memcpy (GST_BUFFER_DATA (h264_data->cached_es) + out_offset,
          GST_BUFFER_DATA (data->codec_data) + offset, sps_size);

      out_offset += sps_size;
      offset += sps_size;
    }


    nb_pps = GST_READ_UINT8 (GST_BUFFER_DATA (data->codec_data) + offset);
    GST_LOG_OBJECT (mux, "we have %d Picture Parameter Set", nb_sps);
    offset++;


    for (i = 0; i < nb_pps; i++) {
      gint pps_size =
          GST_READ_UINT16_BE (GST_BUFFER_DATA (data->codec_data) + offset);

      GST_LOG_OBJECT (mux, "Picture Parameter Set is %d bytes", pps_size);


      offset += 2;


      memcpy (GST_BUFFER_DATA (h264_data->cached_es) + out_offset,
          startcode, 4);
      out_offset += 4;

      memcpy (GST_BUFFER_DATA (h264_data->cached_es) + out_offset,
          GST_BUFFER_DATA (data->codec_data) + offset, pps_size);

      out_offset += pps_size;
      offset += pps_size;
    }
    GST_BUFFER_SIZE (h264_data->cached_es) = out_offset;
    GST_DEBUG_OBJECT (mux, "generated a %" G_GSIZE_FORMAT
        " bytes SPS/PPS header", out_offset);
  }
  return ret;
}
