theora_enc_read_multipass_cache (GstTheoraEnc * enc)
{
  GstBuffer *cache_buf;
  const guint8 *cache_data;
  gsize bytes_read = 0;
  gint bytes_consumed = 0;
  GIOStatus stat = G_IO_STATUS_NORMAL;
  gboolean done = FALSE;

  while (!done) {
    if (gst_adapter_available (enc->multipass_cache_adapter) == 0) {
      cache_buf = gst_buffer_new_and_alloc (512);
      stat = g_io_channel_read_chars (enc->multipass_cache_fd,
          (gchar *) GST_BUFFER_DATA (cache_buf), GST_BUFFER_SIZE (cache_buf),
          &bytes_read, NULL);

      if (bytes_read <= 0) {
        gst_buffer_unref (cache_buf);
        break;
      } else {
        GST_BUFFER_SIZE (cache_buf) = bytes_read;

        gst_adapter_push (enc->multipass_cache_adapter, cache_buf);
      }
    }
    if (gst_adapter_available (enc->multipass_cache_adapter) == 0)
      break;

    bytes_read =
        MIN (gst_adapter_available (enc->multipass_cache_adapter), 512);

    cache_data = gst_adapter_peek (enc->multipass_cache_adapter, bytes_read);

    bytes_consumed =
        th_encode_ctl (enc->encoder, TH_ENCCTL_2PASS_IN, (guint8 *) cache_data,
        bytes_read);
    done = bytes_consumed <= 0;
    if (bytes_consumed > 0)
      gst_adapter_flush (enc->multipass_cache_adapter, bytes_consumed);
  }

  if (stat == G_IO_STATUS_ERROR || (stat == G_IO_STATUS_EOF && bytes_read == 0)
      || bytes_consumed < 0) {
    GST_ELEMENT_ERROR (enc, RESOURCE, READ, (NULL),
        ("Failed to read multipass cache file"));
    return FALSE;
  }
  return TRUE;
}
