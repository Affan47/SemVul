create_recipe_cb(gpointer window, guint action, GtkWidget *menu_item)
{
	GtkWidget *dialog;

	dialog = gtk_object_get_data(GTK_OBJECT(window), "mkrcp_dialog");
	if (dialog == NULL) {
		dialog = create_create_recipe();
		gtk_object_set_data(GTK_OBJECT(dialog), "im_window",
					 window);
		gtk_object_set_data_full(GTK_OBJECT(window), "mkrcp_dialog",
					 dialog, (GtkDestroyNotify)(gtk_widget_destroy));
		gtk_signal_connect (GTK_OBJECT (dialog), "destroy",
				    GTK_SIGNAL_FUNC (close_mkrcp), window);
		set_named_callback (GTK_OBJECT (dialog), "mkrcp_close_button", "clicked",
				    GTK_SIGNAL_FUNC (close_mkrcp_dialog));
		set_named_callback (GTK_OBJECT (dialog), "mkrcp_ok_button", "clicked",
				    GTK_SIGNAL_FUNC (mkrcp_ok_cb));
		set_named_callback (GTK_OBJECT (dialog), "browse_file_button", "clicked",
				    GTK_SIGNAL_FUNC (browse_cb));
		set_named_callback (GTK_OBJECT (dialog), "recipe_file_entry", "activate",
				    GTK_SIGNAL_FUNC (mkrcp_ok_cb));
		update_rcp_dialog(window, dialog);
		gtk_widget_show(dialog);
	} else {
		update_rcp_dialog(window, dialog);
		gtk_widget_show(dialog);
		gdk_window_raise(dialog->window);
	}
}
