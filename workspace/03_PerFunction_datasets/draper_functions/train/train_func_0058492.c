show_about(GtkWidget * widget, gpointer data)
{
  GtkWidget *la, *bu;

  if (about_dialog && about_dialog->window) {
    gdk_window_show(about_dialog->window);

    gdk_window_raise(about_dialog->window);
    return;
  }
  about_dialog = gtk_dialog_new();

  g_signal_connect(G_OBJECT(about_dialog), "destroy", G_CALLBACK(gtk_widget_destroyed), &about_dialog);

  gtk_window_set_wmclass(GTK_WINDOW(about_dialog), "about", "glfer");
  gtk_window_set_title(GTK_WINDOW(about_dialog), "About glfer");
  gtk_window_set_policy(GTK_WINDOW(about_dialog), FALSE, FALSE, FALSE);
  gtk_window_position(GTK_WINDOW(about_dialog), GTK_WIN_POS_CENTER);


  gtk_container_border_width(GTK_CONTAINER(GTK_DIALOG(about_dialog)->vbox), 5);


  bu = gtk_button_new_with_label("Ok");
  gtk_tooltips_set_tip(glfer.tt, bu, "Close window", NULL);
  g_signal_connect_swapped(G_OBJECT(bu), "clicked", G_CALLBACK(gtk_widget_destroy), GTK_OBJECT(about_dialog));
  GTK_WIDGET_SET_FLAGS(bu, GTK_CAN_DEFAULT);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about_dialog)->action_area), bu, TRUE, TRUE, 0);
  gtk_widget_grab_default(bu);
  gtk_widget_show(bu);


  la = gtk_label_new(PACKAGE_NAME " " PACKAGE_VERSION
#ifdef RELDATE
		     "  (" RELDATE ")\n"
#endif
		     "\n" "(C) 2001-2010 Claudio Girardi, <in3otd@qsl.net>\n"
		     "\n" "(C) 2006 Edouard Griffiths, <f4exb@free.fr>\n" );

  gtk_misc_set_padding(GTK_MISC(la), 40, 40);

  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about_dialog)->vbox), la, TRUE, TRUE, 0);
  gtk_widget_show(la);

  gtk_widget_show(about_dialog);
}
