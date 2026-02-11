update_histogram(GtkWidget *dialog)
{
	GtkWidget *darea;

	darea = gtk_object_get_data(GTK_OBJECT(dialog), "hist_area");
	if (darea == NULL)
		return;
	gtk_widget_queue_draw(darea);
}
