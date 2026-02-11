on_text_window_button_release     (GtkWidget       *win,
                                   GdkEventButton  *ev,
                                   gpointer         user_data)
{

  if (ev->button != 1)
    {
      return TRUE;
    }

#ifdef _WIN32
  gboolean above = is_above_virtual_keyboard (ev->x_root, ev->y_root);

  if (above)
    {

      grab_pointer (text_data->window, TEXT_MOUSE_EVENTS);

      return TRUE;
    }

#endif

  if ((text_data) && (text_data->pos))
    {
      save_text ();

      text_data->pos->x = ev->x_root;
      text_data->pos->y = ev->y_root;
      move_editor_cursor ();


      gtk_window_present (GTK_WINDOW (get_bar_window ()));
      gtk_window_present (GTK_WINDOW (text_data->window));
      gdk_window_raise (gtk_widget_get_window  (text_data->window));

      stop_virtual_keyboard ();
      start_virtual_keyboard ();

      text_data->timer = g_timeout_add (1000, blink_cursor, NULL);
    }

  return TRUE;
}
