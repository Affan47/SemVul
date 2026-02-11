meta_ui_remove_event_func (Display       *xdisplay,
                           MetaEventFunc  func,
                           gpointer       data)
{
  g_return_if_fail (ef != NULL);

  gdk_window_remove_filter (NULL, filter_func, ef);

  g_free (ef);
  ef = NULL;
}
