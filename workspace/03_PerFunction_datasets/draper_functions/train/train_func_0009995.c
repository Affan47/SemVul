tip_schedule_cb(gpointer data)
{
	ViewFile *vf = data;
	GtkWidget *window;

	if (!VFICON(vf)->tip_delay_id) return FALSE;

	window = gtk_widget_get_toplevel(vf->listview);

#if GTK_CHECK_VERSION(2,20,0)
	if (gtk_widget_get_sensitive(window) &&
#else
	if (GTK_WIDGET_SENSITIVE(window) &&
#endif
	    GTK_WINDOW(window)->has_focus)
		{
		tip_show(vf);
		}

	VFICON(vf)->tip_delay_id = 0;
	return FALSE;
}
