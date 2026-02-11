sliders_show (struct slider_window_s *window, guint page,
			  gboolean unused)
{
  guint current =
    (guint) gtk_notebook_get_current_page (GTK_NOTEBOOK(window->tabbox));
  window->is_visible = (page != (guint) -1 && page != current)
		       ? TRUE : !window->is_visible;
  if (window->is_visible)
  {
    window_show (window->window, NULL);
    if (page < NUM_PAGES)
      gtk_notebook_set_current_page (GTK_NOTEBOOK(window->tabbox), page);
  }
  else
    gtk_widget_hide (window->window);
}
