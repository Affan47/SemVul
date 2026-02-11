cb_volume_button_clicked (GtkWidget *widget, gpointer data)
{
	if (GTK_WIDGET_VISIBLE (data))
		gtk_widget_hide (data);
	else
		gtk_widget_show (data);
		gimmix_reposition_volume_window (data);
	return;
}
