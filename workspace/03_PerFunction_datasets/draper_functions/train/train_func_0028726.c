fancy_prefs_cb(GtkWidget *widget, GdkEventButton *ev, FancyViewer *viewer)
{
	if ((ev->button == 1) && (ev->type == GDK_BUTTON_PRESS)) {
		gtk_menu_popup(GTK_MENU(viewer->fancy_prefs_menu), NULL, NULL, NULL, NULL,
				ev->button, ev->time);
		return TRUE;
	}
	return FALSE;
}
