create (GSList * group, GtkWidget * pfixed, gint x, gint y, gint w,
		   gint h, GdkPixmap * pix_1, GdkPixmap * pix_2, void (*func) (int), int data)
{
	init ();

	pix_normal = pix_1;
	pix_selected = pix_2;
	runfunc = func;
	func_data = data;

	fixed = gtk_fixed_new ();
	gtk_widget_set_events (fixed, GDK_BUTTON_RELEASE_MASK | GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK);
	gtk_widget_set_size_request (fixed, w, h);
	gtk_fixed_set_has_window(GTK_FIXED(fixed),TRUE);

	gtk_fixed_put (GTK_FIXED (pfixed), fixed, x, y);
	label = gtk_label_new ("");
	SetFont(label,false);
	gtk_fixed_put (GTK_FIXED (fixed), label, 6, 0);
	gtk_widget_show (label);

	gtk_widget_show (fixed);
	g_signal_connect (G_OBJECT (fixed), "button_release_event",
			  G_CALLBACK(on_listitem_button_release), this);
	g_signal_connect (G_OBJECT (fixed), "button_press_event",
			  G_CALLBACK(on_listitem_button_press), this);
	g_signal_connect (G_OBJECT (fixed), "enter_notify_event",
			  G_CALLBACK(on_listitem_enter_notify), this);
	g_signal_connect (G_OBJECT (fixed), "leave_notify_event",
			  G_CALLBACK(on_listitem_leave_notify), this);

	SetBackPixmap (fixed, pix_normal);
	gdk_window_set_cursor (fixed->window, Skin->reciteword.hand_cursor.cursor);

	if (group)
		set_group (group);
}
