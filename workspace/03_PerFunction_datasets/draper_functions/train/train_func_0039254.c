create (GSList * group, GtkWidget * fixed, gint x, gint y,
		      GdkPixmap * pix_1, GdkPixmap * pix_2, GdkPixmap * pix_3,
		      GdkPixmap * pix_4, void (*func) (const gpointer), const gpointer funcdata1)
{
	init ();

	pix_t_normal = pix_1;
	pix_t_down = pix_2;
	pix_f_normal = pix_3;
	pix_f_down = pix_4;
	runfunc = func;
	funcdata = funcdata1;


	event_box = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), event_box, x, y);
	pixmap_widget = gtk_image_new_from_pixmap (pix_f_normal, (GdkBitmap *) NULL);
	gtk_container_add (GTK_CONTAINER (event_box), pixmap_widget);
	g_signal_connect (G_OBJECT (event_box), "button_press_event",
			  G_CALLBACK (on_radiobutton_button_press), this);
	g_signal_connect (G_OBJECT (event_box), "button_release_event",
			  G_CALLBACK(on_radiobutton_button_release),
			  this);
	g_signal_connect (G_OBJECT (event_box), "enter_notify_event",
			  G_CALLBACK(on_radiobutton_enter_notify), this);
	g_signal_connect (G_OBJECT (event_box), "leave_notify_event",
			  G_CALLBACK(on_radiobutton_leave_notify), this);

	gtk_widget_realize (event_box);
	gdk_window_set_cursor (event_box->window, Skin->reciteword.hand_cursor.cursor);
	gtk_widget_show_all (event_box);

	if (group)
		set_group (group);
	else
		set_selected (TRUE);
}
