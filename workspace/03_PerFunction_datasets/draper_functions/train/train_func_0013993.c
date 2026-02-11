webx_preview_nav_popup_expose (GtkWidget        *widget,
                               GdkEventExpose   *event,
                               WebxPreview      *preview)
{
  GtkAdjustment *adj;
  gdouble        x, y;
  gdouble        w, h;
  GdkGC         *gc;

  gc = preview->nav_gc;

  gdk_draw_pixbuf (widget->window, gc, preview->nav_thumbnail,
                   0, 0, 0, 0,
                   widget->allocation.width, widget->allocation.height,
                   GDK_RGB_DITHER_NORMAL, 0, 0);

  adj = gtk_range_get_adjustment (GTK_RANGE (preview->hscr));

  x = adj->value / (adj->upper - adj->lower);
  w = adj->page_size / (adj->upper - adj->lower);

  adj = gtk_range_get_adjustment (GTK_RANGE (preview->vscr));

  y = adj->value / (adj->upper - adj->lower);
  h = adj->page_size / (adj->upper - adj->lower);

  if (w >= 1.0 && h >= 1.0)
    return FALSE;

  gdk_gc_set_clip_rectangle (preview->nav_gc, &event->area);

  x = x * (gdouble) widget->allocation.width + WEBX_NAV_PEN_WIDTH / 2;
  y = y * (gdouble) widget->allocation.height + WEBX_NAV_PEN_WIDTH / 2;
  w = MAX (1.0, ceil (w * widget->allocation.width) - WEBX_NAV_PEN_WIDTH);
  h = MAX (1.0, ceil (h * widget->allocation.height) - WEBX_NAV_PEN_WIDTH);

  gdk_draw_rectangle (widget->window, preview->nav_gc,
                      FALSE,
                      x, y, w, h);

  return FALSE;
}
