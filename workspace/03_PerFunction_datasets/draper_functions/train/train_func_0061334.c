on_new_project(G_GNUC_UNUSED GtkMenuItem *menuitem, G_GNUC_UNUSED gpointer user_data)
{
	PropertyDialogElements *e;
	gint response;

	e = build_properties_dialog(FALSE);
	gtk_widget_show_all(e->dialog);

      retry:
	response = gtk_dialog_run(GTK_DIALOG(e->dialog));
	if (response == GTK_RESPONSE_OK)
	{
		gchar *path;
		struct GeanyPrj *prj;

		path = g_build_filename(gtk_entry_get_text(GTK_ENTRY(e->file_name)), ".geanyprj",
					NULL);

		if (g_file_test(path, G_FILE_TEST_EXISTS))
		{
			ui_set_statusbar(TRUE, _("Project file \"%s\" already exists"), path);
			g_free(path);
			goto retry;
		}
		prj = geany_project_new();

		geany_project_set_path(prj, path);
		geany_project_set_base_path(prj, gtk_entry_get_text(GTK_ENTRY(e->base_path)));
		geany_project_set_name(prj, gtk_entry_get_text(GTK_ENTRY(e->name)));
		geany_project_set_description(prj, "");
		geany_project_set_run_cmd(prj, "");
		geany_project_set_type_int(prj, gtk_combo_box_get_active(GTK_COMBO_BOX(e->type)));
		geany_project_set_regenerate(prj,
					     gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON
									  (e->regenerate)));

		geany_project_regenerate_file_list(prj);

		geany_project_save(prj);
		geany_project_free(prj);
		document_open_file(path, FALSE, NULL, NULL);
	}

	gtk_widget_destroy(e->dialog);
	g_free(e);
}
