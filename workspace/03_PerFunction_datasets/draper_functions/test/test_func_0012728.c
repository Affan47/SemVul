get_visual(void)
{
  GdkVisual *visual;

  gtk_widget_push_colormap (gdk_rgb_get_colormap());

  visual = gtk_widget_get_default_visual();

  if (visual->type == GDK_VISUAL_STATIC_GRAY) {

    log_verbose("found B/W display.");
    return BW_DISPLAY;
  }

  if(visual->type < GDK_VISUAL_STATIC_COLOR) {

    log_verbose("found grayscale(?) display.");
    return GRAYSCALE_DISPLAY;
  }

  log_verbose("color system booted ok.");

  return COLOR_DISPLAY;
}
