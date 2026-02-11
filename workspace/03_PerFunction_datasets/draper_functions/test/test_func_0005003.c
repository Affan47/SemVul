count_expose_cb(metro_t* metro, GdkEventExpose *event) {

  if (debug)
    fprintf(stderr, "Virtual Tick / count: expose event: (%d, %d), %d x %d\n",
        event->area.x, event->area.y, event->area.width, event->area.height);

  gdk_draw_drawable(metro->visualtick_count->window,
    metro->visualtick_count->style->fg_gc[GTK_STATE_NORMAL],
    metro->visualtick_count_pixmap,
    event->area.x, event->area.y,
    event->area.x, event->area.y, event->area.width, event->area.height);

  return TRUE;
}
