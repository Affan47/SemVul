create_shutdown_window (void)
{
  GtkWidget *shutdown_window;
  GdkPixbuf *shutdown_window_icon_pixbuf;
  GtkWidget *frame30;
  GtkWidget *vbox44;
  GtkWidget *label184;
  GtkWidget *label_shutdown_count;

  shutdown_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (shutdown_window, "shutdown_window");
  gtk_window_set_title (GTK_WINDOW (shutdown_window), _("gtk-gnutella shutdown"));
  gtk_window_set_position (GTK_WINDOW (shutdown_window), GTK_WIN_POS_MOUSE);
  shutdown_window_icon_pixbuf = create_pixbuf ("icon.48x48.xpm");
  if (shutdown_window_icon_pixbuf)
    {
      gtk_window_set_icon (GTK_WINDOW (shutdown_window), shutdown_window_icon_pixbuf);
      g_object_unref (shutdown_window_icon_pixbuf);
    }

  frame30 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame30, "frame30");
  gtk_widget_show (frame30);
  gtk_container_add (GTK_CONTAINER (shutdown_window), frame30);
  gtk_container_set_border_width (GTK_CONTAINER (frame30), 6);

  vbox44 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox44, "vbox44");
  gtk_widget_show (vbox44);
  gtk_container_add (GTK_CONTAINER (frame30), vbox44);
  gtk_container_set_border_width (GTK_CONTAINER (vbox44), 30);

  label184 = gtk_label_new (_("gtk-gnutella is shutting down.\nSending bye messages to peers.\n\nGrace time remaining:"));
  gtk_widget_set_name (label184, "label184");
  gtk_widget_show (label184);
  gtk_box_pack_start (GTK_BOX (vbox44), label184, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label184), GTK_JUSTIFY_CENTER);

  label_shutdown_count = gtk_label_new ("[time]");
  gtk_widget_set_name (label_shutdown_count, "label_shutdown_count");
  gtk_widget_show (label_shutdown_count);
  gtk_box_pack_start (GTK_BOX (vbox44), label_shutdown_count, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label_shutdown_count), GTK_JUSTIFY_CENTER);

  g_signal_connect ((gpointer) shutdown_window, "delete_event",
                    G_CALLBACK (gtk_true),
                    NULL);


  GLADE_HOOKUP_OBJECT_NO_REF (shutdown_window, shutdown_window, "shutdown_window");
  GLADE_HOOKUP_OBJECT (shutdown_window, frame30, "frame30");
  GLADE_HOOKUP_OBJECT (shutdown_window, vbox44, "vbox44");
  GLADE_HOOKUP_OBJECT (shutdown_window, label184, "label184");
  GLADE_HOOKUP_OBJECT (shutdown_window, label_shutdown_count, "label_shutdown_count");

  return shutdown_window;
}
