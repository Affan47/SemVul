gst_pnmdec_chain_ascii (GstPnmdec * s, GstPad * src, GstBuffer * buf)
{
  GScanner *scanner;
  GstBuffer *out;
  guint i = 0;
  gchar *b = (gchar *) GST_BUFFER_DATA (buf);
  guint bs = GST_BUFFER_SIZE (buf);
  guint target = s->size - (s->buf ? GST_BUFFER_SIZE (s->buf) : 0);

  if (!bs) {
    gst_buffer_unref (buf);
    return GST_FLOW_OK;
  }

  if (s->last_byte) {
    while (*b >= '0' && *b <= '9') {
      s->last_byte = 10 * s->last_byte + *b - '0';
      b++;
      if (!--bs) {
        gst_buffer_unref (buf);
        return GST_FLOW_OK;
      }
    }
    if (s->last_byte > 255) {
      gst_buffer_unref (buf);
      GST_DEBUG_OBJECT (s, "Corrupt ASCII encoded PNM file.");
      return GST_FLOW_ERROR;
    }
  }

  out = gst_buffer_new_and_alloc (target);

  if (s->last_byte) {
    GST_BUFFER_DATA (out)[i++] = s->last_byte;
    s->last_byte = 0;
  }

  scanner = g_scanner_new (NULL);
  g_scanner_input_text (scanner, b, bs);
  while (!g_scanner_eof (scanner)) {
    switch (g_scanner_get_next_token (scanner)) {
      case G_TOKEN_INT:
        if (i == target) {
          GST_DEBUG_OBJECT (s, "PNM file contains too much data.");
          gst_buffer_unref (buf);
          gst_buffer_unref (out);
          return GST_FLOW_ERROR;
        }
        GST_BUFFER_DATA (out)[i++] = scanner->value.v_int;
        break;
      default:
         ;
    }
  }
  g_scanner_destroy (scanner);


  if (i && i < target && b[bs - 1] > '0' && b[bs - 1] <= '9')
    s->last_byte = GST_BUFFER_DATA (out)[--i];

  gst_buffer_unref (buf);
  if (!i) {
    gst_buffer_unref (out);
    return GST_FLOW_OK;
  }

  GST_BUFFER_SIZE (out) = i;
  return gst_pnmdec_chain_raw (s, src, out);
}
