c_one_entry (GtkWidget *bframe,gchar *titre,gchar *mode,gchar *set,guint del)
{
  GtkWidget *fp;
  GtkWidget *frame;
  GtkWidget *vboxall;
  GtkWidget *vboxframe;
  GtkWidget *hbox1;
  GtkWidget *hbox2;
  GtkWidget *button;
  GtkWidget *label;
  GtkWidget *entry;

  fp = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_modal(GTK_WINDOW(fp),TRUE);
  gtk_window_set_title(GTK_WINDOW(fp),titre);
  gtk_container_set_border_width (GTK_CONTAINER (fp), 5);

  gtk_window_set_transient_for(GTK_WINDOW(fp),GTK_WINDOW(Wins));
  gtk_window_set_position(GTK_WINDOW(fp),GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (fp), TRUE);

  add_child(Wins,fp,gtk_widget_destroy,titre);
  g_signal_connect(G_OBJECT(fp),"delete_event",(GCallback)delete_child,NULL);

  vboxall = create_vbox(fp);
  frame = gtk_frame_new (titre);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 5);
  gtk_container_add (GTK_CONTAINER (vboxall), frame);
  gtk_widget_show (frame);

  vboxframe = create_vbox(frame);
   hbox1 = create_hbox(vboxframe);
  label = gtk_label_new (titre);
  gtk_widget_show (label);
  gtk_box_pack_start (GTK_BOX (hbox1), label, TRUE, FALSE, 0);

  entry = gtk_entry_new ();
  gtk_widget_show (entry);
  gtk_box_pack_start (GTK_BOX (hbox1), entry, FALSE, TRUE, 0);
  gtk_entry_set_text(GTK_ENTRY(entry),set);

  hbox2 = create_hbox(vboxall);
  gtk_widget_realize(Window);

  button = create_button(Window,_("Cancel"));
  gtk_box_pack_start (GTK_BOX( hbox2), button, TRUE, TRUE, 3);
  g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK(delete_child),GTK_OBJECT(fp));
  gtk_widget_show (button);

  button = create_button(Window,_("OK"));
  gtk_box_pack_start (GTK_BOX( hbox2), button, TRUE, TRUE, 3);
  gtk_widget_show (button);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gene_one_entry1),(gpointer)mode);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gene_one_entry2),(gpointer)entry);
  if(del) g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK(gtk_widget_destroy),GTK_OBJECT(bframe));
  g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK(delete_child),GTK_OBJECT(fp));


  gtk_widget_show_all(fp);
}
