gst_jpeg_dec_ensure_buffers (GstJpegDec * dec, guint maxrowbytes)
{
  gint i;

  if (G_LIKELY (dec->idr_width_allocated == maxrowbytes))
    return TRUE;


  for (i = 0; i < 16; i++) {
    dec->idr_y[i] = g_try_realloc (dec->idr_y[i], maxrowbytes);
    dec->idr_u[i] = g_try_realloc (dec->idr_u[i], maxrowbytes);
    dec->idr_v[i] = g_try_realloc (dec->idr_v[i], maxrowbytes);

    if (G_UNLIKELY (!dec->idr_y[i] || !dec->idr_u[i] || !dec->idr_v[i])) {
      GST_WARNING_OBJECT (dec, "out of memory, i=%d, bytes=%u", i, maxrowbytes);
      return FALSE;
    }
  }

  dec->idr_width_allocated = maxrowbytes;
  GST_LOG_OBJECT (dec, "allocated temp memory, %u bytes/row", maxrowbytes);
  return TRUE;
}
