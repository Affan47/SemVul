eb_save_size(GtkWidget *widget, gpointer data)
{
	int h = widget->allocation.height;
	int w = widget->allocation.width;
	int x, y;

	if (h < 10 || w < 10)
		return;

	iSetLocalPref("length_contact_window", h);
	iSetLocalPref("width_contact_window", w);

	gtkut_widget_get_uposition(statuswindow, &x, &y);
	iSetLocalPref("x_contact_window", x);
	iSetLocalPref("y_contact_window", y);

	ayttm_prefs_write();
}
