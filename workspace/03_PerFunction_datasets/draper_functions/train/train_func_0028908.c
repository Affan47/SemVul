color_btn_clicked(GtkButton *button, gpointer user_data)
{
	GtkWidget*dlg;
	const gchar *cn=NULL;
	gint resp;
	GdkColor rgb;

	dlg=gtk_color_selection_dialog_new (_("Select Color"));
	make_modal(dlg, gtk_widget_get_toplevel(GTK_WIDGET(user_data)));
	cn=gtk_entry_get_text(GTK_ENTRY(user_data));
	if (cn && *cn && gdk_color_parse(cn,&rgb)) {
		gtk_color_selection_set_current_color(
			GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(dlg)->colorsel), &rgb);
	}
	resp=gtk_dialog_run(GTK_DIALOG(dlg));
	if (resp == GTK_RESPONSE_OK) {
		gchar *rv=NULL;
		gtk_color_selection_get_current_color(
			GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(dlg)->colorsel), &rgb);
		rv=g_strdup_printf("#%2.2X%2.2X%2.2X",rgb.red/256,rgb.green/256,rgb.blue/256);
		gtk_entry_set_text(GTK_ENTRY(user_data), rv);
		g_free(rv);
	}
	gtk_widget_destroy(dlg);
}
