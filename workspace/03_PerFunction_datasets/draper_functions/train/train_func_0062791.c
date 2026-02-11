render_simple (cairo_t     *cr,
               int width, int height,
               MetaGradientType type,
               gboolean    with_alpha)
{
  GdkPixbuf *pixbuf;
  GdkRGBA from, to;

  gdk_rgba_parse (&from, "blue");
  gdk_rgba_parse (&to, "green");

  pixbuf = meta_gradient_create_simple (width, height,
                                        &from, &to,
                                        type);

  if (with_alpha)
    {
      const unsigned char alphas[] = { 0xff, 0xaa, 0x2f, 0x0, 0xcc, 0xff, 0xff };

      if (!gdk_pixbuf_get_has_alpha (pixbuf))
        {
          GdkPixbuf *new_pixbuf;

          new_pixbuf = gdk_pixbuf_add_alpha (pixbuf, FALSE, 0, 0, 0);
          g_object_unref (G_OBJECT (pixbuf));
          pixbuf = new_pixbuf;
        }

      meta_gradient_add_alpha (pixbuf,
                               alphas, G_N_ELEMENTS (alphas),
                               META_GRADIENT_HORIZONTAL);

      draw_checkerboard (cr , width, height);
    }

  gdk_cairo_set_source_pixbuf (cr, pixbuf, 0, 0);
  cairo_rectangle (cr, 0, 0, width, height);
  cairo_fill (cr);

  g_object_unref (G_OBJECT (pixbuf));
}
