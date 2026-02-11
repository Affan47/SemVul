gst_cairo_render_chain (GstPad * pad, GstBuffer * buf)
{
  GstCairoRender *c = GST_CAIRO_RENDER (GST_PAD_PARENT (pad));
  cairo_surface_t *s;
  gboolean success;

  if (G_UNLIKELY (c->width <= 0 || c->height <= 0 || c->stride <= 0))
    return GST_FLOW_NOT_NEGOTIATED;

  if (c->png) {
    GST_BUFFER_OFFSET (buf) = 0;
    s = cairo_image_surface_create_from_png_stream (read_buffer, buf);
  } else {
    if (c->format == CAIRO_FORMAT_ARGB32) {
      guint i, j;
      guint8 *data = GST_BUFFER_DATA (buf);

      buf = gst_buffer_make_writable (buf);


      for (i = 0; i < c->height; i++) {
        for (j = 0; j < c->width; j++) {
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
          guint8 alpha = data[3];

          data[0] = (data[0] * alpha) >> 8;
          data[1] = (data[1] * alpha) >> 8;
          data[2] = (data[2] * alpha) >> 8;
#else
          guint8 alpha = data[0];

          data[1] = (data[1] * alpha) >> 8;
          data[2] = (data[2] * alpha) >> 8;
          data[3] = (data[3] * alpha) >> 8;
#endif
          data += 4;
        }
      }
    }

    s = cairo_image_surface_create_for_data (GST_BUFFER_DATA (buf),
        c->format, c->width, c->height, c->stride);
  }

  success = gst_cairo_render_push_surface (c, s);
  gst_buffer_unref (buf);
  return success ? GST_FLOW_OK : GST_FLOW_ERROR;
}
