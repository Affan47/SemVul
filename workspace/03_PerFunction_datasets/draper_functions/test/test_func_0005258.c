menu_copy_activate_cb(GtkWidget *widget,
                      gpointer data)
{
  GtkTextIter start;
  GtkTextIter end;

  if (gtk_text_buffer_get_selection_bounds(currentWorld->gui->txtBuffer,
                                           &start, &end)) {
    GdkDisplay   *display;
    GtkClipboard *clipboard;

    display = gtk_widget_get_display(GTK_WIDGET(currentWorld->gui->txtView));

    clipboard = gtk_clipboard_get_for_display(display,
                                              GDK_SELECTION_CLIPBOARD);
    gtk_text_buffer_copy_clipboard(currentWorld->gui->txtBuffer, clipboard);


    gtk_text_buffer_select_range(currentWorld->gui->txtBuffer, &start, &end);
  } else {
    simo_combo_box_copy_clipboard(currentWorld->gui->cmbEntry);
  }
}
