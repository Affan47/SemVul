mw_create(gint da_width, gint da_height) {
        GtkWidget *mainwin;
  	GtkWidget *menubar;
  	GtkWidget *vbox, *hbox, *hbox1, *drawing_area_box;
	GtkWidget *timer_label;
  	GdkPixbuf *icon;
	GError *error=NULL;

	mainwin = ut_window_new(_("GtkBalls"), "GtkBalls_Main", "GtkBalls", FALSE, FALSE, FALSE, 0);
  	g_signal_connect(G_OBJECT(mainwin), "destroy", G_CALLBACK(gtk_main_quit), mainwin);

        icon = gdk_pixbuf_new_from_file(DATADIR "/gtkballs/gtkballs_16x16.png", &error);
  	if(icon) {
		gtk_window_set_icon(GTK_WINDOW(mainwin), icon);
        } else {
                g_error_free(error);
        }

  	vbox = gtk_vbox_new(FALSE, 5);
  	gtk_container_add(GTK_CONTAINER(mainwin), vbox);

  	menu_get_main(mainwin, &menubar);
        menu_set_sensitive_undo(FALSE);
  	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, TRUE, 0);

  	hbox = gtk_hbox_new(FALSE, 0);
  	_hi_score_label = gtk_label_new("");
  	gtk_box_pack_start(GTK_BOX(hbox), _hi_score_label, FALSE, FALSE, 5);
  	_user_score_label = gtk_label_new("");
  	gtk_box_pack_end(GTK_BOX(hbox), _user_score_label, FALSE, FALSE, 5);
  	gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(hbox), FALSE, FALSE, 0);

  	_small_balls_box = gtk_hbox_new(TRUE, 0);
  	gtk_box_pack_start(GTK_BOX(hbox), _small_balls_box, TRUE, FALSE, 0);

  	hbox1 = gtk_hbox_new(FALSE, 0);
        timer_label = gtk_label_new(NULL);
  	gtk_box_pack_start(GTK_BOX(hbox1), timer_label, TRUE, TRUE, 5);
	g_timeout_add(250, _countdown_timer, timer_label);
  	gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(hbox1), FALSE, FALSE, 0);

  	drawing_area_box = gtk_hbox_new(FALSE, 0);
  	gtk_box_pack_start(GTK_BOX(vbox), drawing_area_box, FALSE, FALSE, 10);
  	_drawing_area = gtk_drawing_area_new();
        gtk_widget_set_size_request(_drawing_area, da_width, da_height);
  	gtk_box_pack_start(GTK_BOX(drawing_area_box), _drawing_area, TRUE, FALSE, 10);
  	gtk_widget_set_events(_drawing_area, GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK | GDK_KEY_PRESS_MASK | GDK_POINTER_MOTION_MASK);
  	g_signal_connect(G_OBJECT(_drawing_area), "expose_event", G_CALLBACK(expose_event), NULL);
  	g_signal_connect(G_OBJECT(_drawing_area), "button_press_event", G_CALLBACK(_user_action_event), NULL);
  	g_signal_connect(G_OBJECT(_drawing_area), "motion_notify_event", G_CALLBACK(_user_action_event), NULL);

  	g_signal_connect(G_OBJECT(mainwin), "key_press_event", G_CALLBACK(_user_action_event), NULL);

  	gtk_widget_show_all(mainwin);
}
