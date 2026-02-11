show_preferences_dialog (GtkAction     *action,
			 charpick_data *curr_data)
{
  if (curr_data->propwindow) {
    gtk_window_set_screen (GTK_WINDOW (curr_data->propwindow),
			   gtk_widget_get_screen (curr_data->applet));
    gtk_window_present (GTK_WINDOW (curr_data->propwindow));
    return;
  }

  curr_data->propwindow = gtk_dialog_new_with_buttons (_("Character Palette Preferences"),
  					    NULL,
					    GTK_DIALOG_DESTROY_WITH_PARENT,
					    GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE,
					    GTK_STOCK_HELP, GTK_RESPONSE_HELP,
					    NULL);
  gtk_window_set_screen (GTK_WINDOW (curr_data->propwindow),
			 gtk_widget_get_screen (curr_data->applet));
  gtk_window_set_default_size (GTK_WINDOW (curr_data->propwindow), 350, 350);
  gtk_container_set_border_width (GTK_CONTAINER (curr_data->propwindow), 5);
  gtk_box_set_spacing (GTK_BOX (gtk_dialog_get_content_area(GTK_DIALOG (curr_data->propwindow))), 2);
  gtk_dialog_set_default_response (GTK_DIALOG (curr_data->propwindow), GTK_RESPONSE_CLOSE);

  default_chars_frame_create(curr_data);
  g_signal_connect (G_OBJECT (curr_data->propwindow), "response",
  		    G_CALLBACK (response_cb), curr_data);

  gtk_widget_show_all (curr_data->propwindow);
}
