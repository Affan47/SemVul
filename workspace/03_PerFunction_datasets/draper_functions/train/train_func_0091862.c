close_image_window(x11_image_window_id window_id)
{
  x11_image_window *window;

  if (window_id > space_for_x11_image_windows-1)
    return -1;

  window = x11_image_windows[window_id];
  if (window == NULL)
    return -1;

  if (window->pixmap_stored == true)
  {
    XFreePixmap(x11_display, window->pixmap);
  }

  free_zimage(window->zimage);

  if (window->callback != NULL)
    window->callback(window_id, DRILBO_IMAGE_WINDOW_CLOSED);

  XDestroyWindow(x11_display, window->window);
  XFlush(x11_display);

  x11_image_windows[window_id] = NULL;
  free(window);

  return 0;
}
