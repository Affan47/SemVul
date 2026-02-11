cb_add_button_clicked (GtkWidget *widget, gpointer data)
{
	if (!GTK_WIDGET_VISIBLE(GTK_WINDOW(data)))
		gtk_widget_show (GTK_WIDGET(data));

	gtk_window_present (GTK_WINDOW(data));
	return;
}
