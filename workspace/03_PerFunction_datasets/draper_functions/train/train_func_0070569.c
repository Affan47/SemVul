set_cursor_recurse (GtkWidget * widget, GdkCursor * gdk_cursor)
{
  GList *children, *list;

  if (!gtk_widget_get_visible (widget) || !gtk_widget_get_realized (widget))
    return;

  gdk_window_set_cursor (gtk_widget_get_window (widget), gdk_cursor);

  if (GTK_IS_CONTAINER (widget) &&
      (children =
       glade_util_container_get_all_children (GTK_CONTAINER (widget))) != NULL)
    {
      for (list = children; list; list = list->next)
        {
          set_cursor_recurse (GTK_WIDGET (list->data), gdk_cursor);
        }
      g_list_free (children);
    }
}
