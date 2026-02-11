on_color_scheme_changed(GtkTreeSelection *treesel, gpointer dummy)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *fname;
	gchar *path;

	if (!gtk_tree_selection_get_selected(treesel, &model, &iter))
		return;
	gtk_tree_model_get(model, &iter, SCHEME_FILE, &fname, -1);


	if (!fname)
	{
		SETPTR(editor_prefs.color_scheme, NULL);
		filetypes_reload();
		return;
	}
	SETPTR(fname, utils_get_locale_from_utf8(fname));


	path = g_build_path(G_DIR_SEPARATOR_S, app->configdir, GEANY_COLORSCHEMES_SUBDIR, fname, NULL);
	if (!g_file_test(path, G_FILE_TEST_EXISTS))
	{

		g_free(path);
		path = g_build_path(G_DIR_SEPARATOR_S, app->datadir, GEANY_COLORSCHEMES_SUBDIR, fname, NULL);
	}
	if (g_file_test(path, G_FILE_TEST_EXISTS))
	{
		SETPTR(editor_prefs.color_scheme, fname);
		fname = NULL;
		filetypes_reload();
	}
	else
	{
		SETPTR(fname, utils_get_utf8_from_locale(fname));
		ui_set_statusbar(TRUE, _("Could not find file '%s'."), fname);
	}
	g_free(path);
	g_free(fname);
}
