fill_buffer (GZHandle *gz,
             gsize num_bytes)
{
  gsize count;

  z_stream * zstream = &gz->zstream;

  if (zstream->avail_in > 0) {
    return TRUE;
  }

  count = g_input_stream_read (gz->parent_str,
                               gz->buffer,
                               Z_BUFSIZE,
                               NULL, NULL);
  if (count == -1) {
    if (zstream->avail_out == num_bytes) {
      return FALSE;
    }
    gz->last_str_result = FALSE;
  } else {
    zstream->next_in = gz->buffer;
    zstream->avail_in = count;
  }

  return TRUE;
}
