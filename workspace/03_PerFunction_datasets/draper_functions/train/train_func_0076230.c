status_show_callback(GtkWidget *w, gpointer data)
{
	int newdata = GPOINTER_TO_INT(data);

	if (newdata == status_show)
		return;

	status_show = newdata;
	iSetLocalPref("status_show_level", status_show);
	update_contact_list();
}
