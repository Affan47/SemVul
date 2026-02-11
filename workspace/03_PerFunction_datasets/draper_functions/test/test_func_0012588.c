on_save_button_clicked (GtkButton *button, gpointer user_data)
{
	GtkWidget *label;
	gchar     *labeltext;
	gint       result;

	savedialog = create_save_dialog ();
	gtk_window_set_transient_for (GTK_WINDOW (savedialog), GTK_WINDOW (gcolor2));

	labeltext = g_strdup_printf (_("Enter a color name for %s:"), hex_value (colorvalue));
	label = lookup_widget (savedialog, "save_label");
	gtk_label_set_markup (GTK_LABEL (label), labeltext);
	result = gtk_dialog_run (GTK_DIALOG (savedialog));
	switch (result)
	{
		case GTK_RESPONSE_OK:

			if (save_selected_color ())
				add_color_to_treeview ();
			break;
		case GTK_RESPONSE_CANCEL:
		default:
			colorname = "";
			break;
	}
	gtk_widget_destroy (savedialog);
}
