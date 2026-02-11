setup_config_file_menus(void)
{
	gchar *f;

	f = g_build_filename(app->configdir, "filetype_extensions.conf", NULL);
	ui_add_config_file_menu_item(f, NULL, NULL);
	SETPTR(f, g_build_filename(app->configdir, GEANY_FILEDEFS_SUBDIR, "filetypes.common", NULL));
	ui_add_config_file_menu_item(f, NULL, NULL);
	g_free(f);

	g_signal_connect(geany_object, "document-save", G_CALLBACK(on_document_save), NULL);
}
