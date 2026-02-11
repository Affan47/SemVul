cb_key_pressed_left_side(GtkWidget   *widget,
                                         GdkEventKey *event,
                                         gpointer     next_widget)
{
   GtkTextBuffer *text_buffer;
   GtkTextIter    iter;

   if (event->keyval == GDK_Return) {
      gtk_signal_emit_stop_by_name(GTK_OBJECT(widget), "key_press_event");
      gtk_widget_grab_focus(GTK_WIDGET(next_widget));

      text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(next_widget));
      gtk_text_buffer_get_start_iter(text_buffer, &iter);
      gtk_text_buffer_place_cursor(text_buffer, &iter);
      return TRUE;
   }

   return FALSE;
}
