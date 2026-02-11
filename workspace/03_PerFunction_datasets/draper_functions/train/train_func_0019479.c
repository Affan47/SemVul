create_fileselection_fd (void)
{
  GtkWidget *fileselection_fd;
  GtkWidget *ok_button_fd;
  GtkWidget *cancel_button_fd;

  fileselection_fd = gtk_file_selection_new ("HOZ");
  gtk_container_set_border_width (GTK_CONTAINER (fileselection_fd), 10);
  gtk_window_set_position (GTK_WINDOW (fileselection_fd), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (fileselection_fd), TRUE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (fileselection_fd), TRUE);

  ok_button_fd = GTK_FILE_SELECTION (fileselection_fd)->ok_button;
  gtk_widget_show (ok_button_fd);
  GTK_WIDGET_SET_FLAGS (ok_button_fd, GTK_CAN_DEFAULT);

  cancel_button_fd = GTK_FILE_SELECTION (fileselection_fd)->cancel_button;
  gtk_widget_show (cancel_button_fd);
  GTK_WIDGET_SET_FLAGS (cancel_button_fd, GTK_CAN_DEFAULT);

  g_signal_connect_swapped ((gpointer) ok_button_fd, "clicked",
                            G_CALLBACK (on_ok_button_fd_clicked),
                            GTK_OBJECT (fileselection_fd));
  g_signal_connect ((gpointer) cancel_button_fd, "clicked",
                    G_CALLBACK (on_cancel_button_fd_clicked),
                    NULL);


  GLADE_HOOKUP_OBJECT_NO_REF (fileselection_fd, fileselection_fd, "fileselection_fd");
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection_fd, ok_button_fd, "ok_button_fd");
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection_fd, cancel_button_fd, "cancel_button_fd");

  return fileselection_fd;
}
