psmux_ensure_system_header (PsMux * mux)
{
  GstBuffer *buf;
  bits_buffer_t bw;
  guint len = 12 + (mux->nb_streams +
      (mux->nb_private_streams > 1 ? mux->nb_private_streams - 1 : 0)) * 3;
  GList *cur;
  gboolean private_hit = FALSE;

  if (mux->sys_header != NULL)
    return;

  buf = gst_buffer_new_and_alloc (len);


  bits_initwrite (&bw, len, GST_BUFFER_DATA (buf));


  bits_write (&bw, 24, PSMUX_START_CODE_PREFIX);
  bits_write (&bw, 8, PSMUX_SYSTEM_HEADER);

  bits_write (&bw, 16, len - 6);
  bits_write (&bw, 1, 1);
  bits_write (&bw, 22, mux->rate_bound);
  bits_write (&bw, 1, 1);
  bits_write (&bw, 6, mux->audio_bound);
  bits_write (&bw, 1, 0);
  bits_write (&bw, 1, 0);
  bits_write (&bw, 1, 0);
  bits_write (&bw, 1, 0);
  bits_write (&bw, 1, 1);
  bits_write (&bw, 5, mux->video_bound);
  bits_write (&bw, 1, 0);
  bits_write (&bw, 7, 0x7f);

  for (cur = g_list_first (mux->streams), private_hit = FALSE; cur != NULL;
      cur = g_list_next (cur)) {
    PsMuxStream *stream = (PsMuxStream *) cur->data;

    if (private_hit && stream->stream_id == PSMUX_EXTENDED_STREAM)
      continue;

    bits_write (&bw, 8, stream->stream_id);
    bits_write (&bw, 2, 0x3);
    bits_write (&bw, 1, stream->is_video_stream);
    bits_write (&bw, 13, stream->max_buffer_size / (stream->is_video_stream ? 1024 : 128));

    if (stream->stream_id == PSMUX_EXTENDED_STREAM)
      private_hit = TRUE;
  }

  GST_MEMDUMP ("System Header", GST_BUFFER_DATA (buf), GST_BUFFER_SIZE (buf));

  mux->sys_header = buf;
}
