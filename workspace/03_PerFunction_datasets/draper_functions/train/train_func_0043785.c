secure_quit (GtkWidget * widget, void *data)
{
  GtkWidget *finestra, *testo, *tabella, *button_ok, *button_no;
  extern GtkWidget *jeex_main_window;


  finestra = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_transient_for (GTK_WINDOW (finestra), GTK_WINDOW (jeex_main_window));
  gtk_window_set_position (GTK_WINDOW (finestra), GTK_WIN_POS_CENTER_ON_PARENT);
  gtk_window_set_title (GTK_WINDOW (finestra), _("Quit"));
  gtk_window_set_resizable (GTK_WINDOW (finestra), FALSE);


  tabella = gtk_table_new (2, 3, TRUE);
  gtk_container_add (GTK_CONTAINER (finestra), tabella);
  gtk_widget_show (tabella);


  testo = gtk_label_new (_("\n Are you sure to quit Jeex? \n" " ( Unsaved changes will be lost ) \n"));
  gtk_table_attach (GTK_TABLE (tabella), testo, 0, 3, 0, 1, GTK_FILL | GTK_EXPAND, GTK_FILL, 0, 0);
  gtk_widget_show (testo);


  button_ok = gtk_button_new_from_stock (GTK_STOCK_OK);
  gtk_table_attach (GTK_TABLE (tabella), button_ok, 2, 3, 1, 2, GTK_FILL, GTK_FILL, 10, 10);
  gtk_widget_show (button_ok);


  button_no = gtk_button_new_from_stock (GTK_STOCK_CANCEL);
  gtk_table_attach (GTK_TABLE (tabella), button_no, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 10, 10);
  GTK_WIDGET_SET_FLAGS (button_no, GTK_CAN_DEFAULT);
  gtk_widget_grab_default (button_no);
  gtk_widget_show (button_no);

  gtk_widget_show (finestra);


  g_signal_connect (G_OBJECT (button_no), "clicked", G_CALLBACK (destroy_this), (void *) finestra);
  g_signal_connect (G_OBJECT (button_ok), "clicked", G_CALLBACK (gtk_main_quit), NULL);

  return NULL;
}
