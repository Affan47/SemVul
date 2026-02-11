gucharmap_chartable_draw (GtkWidget *widget,
                          cairo_t *cr)
{
  GucharmapChartable *chartable = GUCHARMAP_CHARTABLE (widget);
  GucharmapChartablePrivate *priv = chartable->priv;
  GtkStyle *style;
  int row, col;
  cairo_rectangle_int_t clip_rect;
  cairo_region_t *region;

  if (!gdk_cairo_get_clip_rectangle (cr, &clip_rect))
    return FALSE;

  region = cairo_region_create_rectangle (&clip_rect);

  if (cairo_region_is_empty (region)) {
    cairo_region_destroy (region);
    return FALSE;
  }

#if 0
  {
    int i, n_rects;

    n_rects = cairo_region_num_rectangles (event->region);

    g_print ("Exposing area %d:%d@(%d,%d) with %d rects ", event->area.width, event->area.height,
             event->area.x, event->area.y, n_rects);
    for (i = 0; i < n_rects; ++i) {
      g_print ("[Rect %d:%d@(%d,%d)] ", rects[i].width, rects[i].height, rects[i].x, rects[i].y);
    }
    g_print ("\n");
  }
#endif

  style = gtk_widget_get_style (widget);
  gdk_cairo_set_source_color (cr, &style->bg[GTK_STATE_NORMAL]);
  gdk_cairo_region (cr, region);
  cairo_fill (cr);

  if (priv->codepoint_list == NULL)
    goto expose_done;

  gucharmap_chartable_ensure_pango_layout (chartable);

  for (row = priv->rows - 1; row >= 0; --row)
    {
      for (col = priv->cols - 1; col >= 0; --col)
        {
          cairo_rectangle_int_t rect;

          rect.x = _gucharmap_chartable_x_offset (chartable, col);
          rect.y = _gucharmap_chartable_y_offset (chartable, row);
          rect.width = _gucharmap_chartable_column_width (chartable, col);
          rect.height = _gucharmap_chartable_row_height (chartable, row);

          if (cairo_region_contains_rectangle (region, &rect) == CAIRO_REGION_OVERLAP_OUT)
            continue;

          draw_square_bg (chartable, cr, &rect, row, col);
          draw_character (chartable, cr, &rect, row, col);
        }
    }

  draw_borders (chartable, cr);

expose_done:

  cairo_region_destroy (region);


  return FALSE;
}
