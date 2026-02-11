chatline_is_scrolled_to_bottom(void)
{
  GtkWidget *sw, *w;
  GtkAdjustment *vadj;
  gdouble val, max, upper, page_size;

  if (get_client_page() == PAGE_GAME) {
    w = GTK_WIDGET(main_message_area);
  } else {
    w = GTK_WIDGET(start_message_area);
  }

  if (w == NULL) {
    return TRUE;
  }

  sw = gtk_widget_get_parent(w);
  vadj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(sw));
  val = gtk_adjustment_get_value(vadj);
  g_object_get(G_OBJECT(vadj), "upper", &upper,
               "page-size", &page_size, NULL);
  max = upper - page_size;


  return max - val < 0.00000001;
}
