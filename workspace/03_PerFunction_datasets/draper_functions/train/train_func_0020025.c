sanitize_size (GdkDrawable * window, gint * width, gint * height) {
  if ((*width == -1) && (*height == -1))
    gdk_drawable_get_size (window, width, height);
  else if (*width == -1)
    gdk_drawable_get_size (window, width, NULL);
  else if (*height == -1)
    gdk_drawable_get_size (window, NULL, height);
}
