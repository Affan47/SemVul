gst_jpegenc_term_destination (j_compress_ptr cinfo)
{
  GstBuffer *outbuf;
  GstJpegEnc *jpegenc = (GstJpegEnc *) (cinfo->client_data);
  gsize memory_size = jpegenc->output_map.size - jpegenc->jdest.free_in_buffer;
  GstByteReader reader =
      GST_BYTE_READER_INIT (jpegenc->output_map.data, memory_size);
  guint16 marker;
  gint sof_marker = -1;

  GST_DEBUG_OBJECT (jpegenc, "gst_jpegenc_chain: term_source");


  while (gst_byte_reader_get_uint16_be (&reader, &marker)) {

    if (marker >> 4 == 0x0ffc) {
      sof_marker = marker & 0x4;
      break;
    }
  }

  gst_memory_unmap (jpegenc->output_mem, &jpegenc->output_map);

  gst_memory_resize (jpegenc->output_mem, 0, memory_size);
  jpegenc->output_map.data = NULL;
  jpegenc->output_map.size = 0;

  if (jpegenc->sof_marker != sof_marker) {
    GstVideoCodecState *output;
    output =
        gst_video_encoder_set_output_state (GST_VIDEO_ENCODER (jpegenc),
        gst_caps_new_simple ("image/jpeg", "sof-marker", G_TYPE_INT, sof_marker,
            NULL), jpegenc->input_state);
    gst_video_codec_state_unref (output);
    jpegenc->sof_marker = sof_marker;
  }

  outbuf = gst_buffer_new ();
  gst_buffer_copy_into (outbuf, jpegenc->current_frame->input_buffer,
      GST_BUFFER_COPY_METADATA, 0, -1);
  gst_buffer_append_memory (outbuf, jpegenc->output_mem);
  jpegenc->output_mem = NULL;

  jpegenc->current_frame->output_buffer = outbuf;

  gst_video_frame_unmap (&jpegenc->current_vframe);

  GST_VIDEO_CODEC_FRAME_SET_SYNC_POINT (jpegenc->current_frame);

  jpegenc->res = gst_video_encoder_finish_frame (GST_VIDEO_ENCODER (jpegenc),
      jpegenc->current_frame);
  jpegenc->current_frame = NULL;
}
