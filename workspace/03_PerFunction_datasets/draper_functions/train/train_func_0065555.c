import_cancel_cb(GtkWidget *widget, gpointer data)
{
	if (gtk_main_level() > 1)
		gtk_main_quit();
}
