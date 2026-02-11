create_table_prop()
{
   GtkWidget *WinTable;
   GtkWidget *frame;
   GtkWidget *vbox;
   GtkWidget *hbox;
   GtkWidget* button;

  WinTable = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(WinTable),_("Select your atom"));
  gtk_window_set_position(GTK_WINDOW(WinTable),GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW(WinTable),(gint)(ScreenWidth*0.5),(gint)(ScreenHeight*0.4));

  g_signal_connect(G_OBJECT(WinTable), "delete_event", (GCallback)destroy_button_windows, NULL);
  g_signal_connect(G_OBJECT(WinTable), "delete_event", (GCallback)gtk_widget_destroy, NULL);

  vbox = gtk_vbox_new (FALSE, 2);
  gtk_container_add(GTK_CONTAINER(WinTable),vbox);

  hbox = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);

  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type( GTK_FRAME(frame),GTK_SHADOW_ETCHED_OUT);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 0);
  gtk_container_add(GTK_CONTAINER(hbox),frame);
  gtk_widget_show (frame);

  create_table_prop_in_window(WinTable,frame);

  hbox = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 2);
  gtk_widget_realize(WinTable);
  button = create_button(WinTable,_("Close"));
  gtk_box_pack_end (GTK_BOX (hbox), button, FALSE, FALSE, 2);
  g_signal_connect_swapped(G_OBJECT(button),"clicked", (GCallback)destroy_button_windows, GTK_OBJECT(WinTable));
  g_signal_connect_swapped(G_OBJECT(button), "clicked", (GCallback)gtk_widget_destroy, GTK_OBJECT(WinTable));
  GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default(button);
  gtk_widget_show(button);

  add_button_windows(_(" Properties "),WinTable);

  gtk_widget_show_all(WinTable);
}
