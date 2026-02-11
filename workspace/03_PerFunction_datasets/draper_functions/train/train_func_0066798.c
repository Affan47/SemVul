get_sliders (const struct slider_window_s *window, guint page)
{
  if (page >= NUM_PAGES)
  {
    page = (guint) gtk_notebook_get_current_page (GTK_NOTEBOOK(window->tabbox));
    if (page >= NUM_PAGES)
      return NULL;
  }
  return window->sliders[page].sliders;
}
