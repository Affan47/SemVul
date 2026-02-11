gmlc_gui_connexions_evt_delete (GtkWidget *widget, GdkEvent *event, gpointer user_data) {
	UNUSED_VAR(event);
	UNUSED_VAR(user_data);

	gtk_widget_hide(GTK_WIDGET(widget));

	if (GiNbrWnd <= 0) {
		gtk_main_quit();
		return TRUE;
	}

	return FALSE;
}
