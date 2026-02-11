draw_pixel_value (cairo_t *cr,
                  GdkRGBA *bg, GdkRGBA *fg,
                  gdouble x, gdouble y,
                  gboolean rotate,
                  gboolean draw_border,
                  gint val)
{
  cairo_text_extents_t extents;
  gchar pixel_str[8];

  g_snprintf (pixel_str, 8, "%d", val);

  cairo_text_extents (cr, pixel_str, &extents);

  cairo_save (cr);

  if (rotate)
    {
      cairo_translate (cr, x - 1.5, y + .5 + extents.width/2);
      cairo_rotate (cr, G_PI/-2);
    }
  else
    cairo_translate (cr, x - (extents.width+extents.x_bearing)/2, y - 2);

  cairo_move_to (cr, 0, 0);

  if (draw_border || extents.width + 4 >= val)
    {
      cairo_set_source_rgba (cr, bg->red, bg->green, bg->blue, .9);

      cairo_text_path (cr, pixel_str);
      cairo_set_line_width (cr, 3);
      cairo_stroke (cr);

      cairo_set_line_width (cr, 1);
      gdk_cairo_set_source_rgba (cr, fg);
    }

  cairo_show_text (cr, pixel_str);

  cairo_restore (cr);
}
