get_named_checkb_val(GtkWidget *dialog, char *name)
{
	GtkWidget * wid;
	wid = gtk_object_get_data(GTK_OBJECT(dialog), name);
	g_return_val_if_fail(wid != NULL, 0);
	return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid));
}
