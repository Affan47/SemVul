treeview_key_pressed(GtkWidget *widget, GdkEventKey *event, GtkWidget *search_window)
{
  switch (event->keyval) {
    case XK_Escape:
    case XK_Home:
    case XK_Up:
    case XK_Down:
    case XK_Page_Up:
    case XK_Page_Down:
    case XK_End:
    case XK_Shift_L:
    case XK_Shift_R:
    case XK_Control_L:
    case XK_Control_R:
    case XK_Tab:
      return FALSE;
    case XK_Return:
      search_doubleclick();
      gtk_widget_destroy(search_window);
      break;
    case XK_Delete:
      remove_selected();
      break;
  }
  return TRUE;
}
