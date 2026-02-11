update_file_patterns(GtkWidget *mode_combo, GtkWidget *fcombo)
{
	gint selection;
	GtkWidget *entry;

	entry = gtk_bin_get_child(GTK_BIN(fcombo));

	selection = gtk_combo_box_get_active(GTK_COMBO_BOX(mode_combo));

	if (selection == FILES_MODE_ALL)
	{
		gtk_entry_set_text(GTK_ENTRY(entry), "");
		gtk_widget_set_sensitive(fcombo, FALSE);
	}
	else if (selection == FILES_MODE_CUSTOM)
	{
		gtk_widget_set_sensitive(fcombo, TRUE);
	}
	else if (selection == FILES_MODE_PROJECT)
	{
		if (app->project && NZV(app->project->file_patterns))
		{
			gchar *patterns;

			patterns = g_strjoinv(" ", app->project->file_patterns);
			gtk_entry_set_text(GTK_ENTRY(entry), patterns);
			g_free(patterns);
		}
		else
		{
			gtk_entry_set_text(GTK_ENTRY(entry), "");
		}

		gtk_widget_set_sensitive(fcombo, FALSE);
	}
}
