run_open_dialog(GtkDialog *dialog)
{
	while (gtk_dialog_run(dialog) == GTK_RESPONSE_ACCEPT)
	{
		gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));


		if (! project_load_file_with_session(filename))
		{
			gchar *utf8_filename = utils_get_utf8_from_locale(filename);

			SHOW_ERR1(_("Project file \"%s\" could not be loaded."), utf8_filename);
			gtk_widget_grab_focus(GTK_WIDGET(dialog));
			g_free(utf8_filename);
			g_free(filename);
			continue;
		}
		g_free(filename);
		break;
	}
}
