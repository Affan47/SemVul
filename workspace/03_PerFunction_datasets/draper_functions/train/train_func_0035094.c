psmux_ensure_program_stream_map (PsMux * mux)
{
  GstBuffer *buf;
  gint psm_size = 16, es_map_size = 0;
  bits_buffer_t bw;
  GList *cur;
  guint16 len;
  guint8 *pos;

  if (mux->psm != NULL)
    return;


  pos = mux->es_info_buf;
  for (cur = g_list_first (mux->streams); cur != NULL; cur = g_list_next (cur)) {
    PsMuxStream *stream = (PsMuxStream *) cur->data;
    len = 0;

    *pos++ = stream->stream_type;
    *pos++ = stream->stream_id;

    psmux_stream_get_es_descrs (stream, pos + 2, &len);
    psmux_put16 (&pos, len);

    es_map_size += len + 4;
    pos += len;
#if 0
    if (stream->lang[0] != 0)
      es_map_size += 6;
#endif
  }

  psm_size += es_map_size;

  buf = gst_buffer_new_and_alloc (psm_size);

  bits_initwrite (&bw, psm_size, GST_BUFFER_DATA (buf));


  bits_write (&bw, 24, PSMUX_START_CODE_PREFIX);
  bits_write (&bw, 8, PSMUX_PROGRAM_STREAM_MAP);

  bits_write (&bw, 16, psm_size - 6);
  bits_write (&bw, 1, 1);
  bits_write (&bw, 2, 0xF);
  bits_write (&bw, 5, 0x1);
  bits_write (&bw, 7, 0xFF);
  bits_write (&bw, 1, 1);

  bits_write (&bw, 16, 0);


  bits_write (&bw, 16, es_map_size);

  memcpy (bw.p_data + bw.i_data, mux->es_info_buf, es_map_size);


  {
    guint32 crc = calc_crc32 (bw.p_data, psm_size - 4);
    guint8 *pos = bw.p_data + psm_size - 4;
    psmux_put32 (&pos, crc);
  }

  GST_MEMDUMP ("Program Stream Map", GST_BUFFER_DATA (buf),
      GST_BUFFER_SIZE (buf));

  mux->psm = buf;
}
