expose_event (Waterfall *waterfall,
              GdkEventExpose *event)
{
  gdk_window_set_back_pixmap (GTK_WIDGET (waterfall)->window, NULL, FALSE);

  if (waterfall->pixmap == NULL)
    draw_pixmap (waterfall);

  gdk_draw_drawable (GTK_WIDGET (waterfall)->window,
                     GTK_WIDGET (waterfall)->style->fg_gc[GTK_STATE_NORMAL],
                     waterfall->pixmap,
                     event->area.x, event->area.y,
                     event->area.x, event->area.y,
                     event->area.width, event->area.height);

  return FALSE;
}
