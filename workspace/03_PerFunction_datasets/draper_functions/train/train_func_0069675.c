save_config_file(void)
{
	FILE *fp;
	gchar *path;
	GtkItemFactory *ifactory;
	gint width, height;
	gchar *fontname;
	gboolean wordwrap, linenumbers, autoindent;

	gtk_window_get_size(GTK_WINDOW(pub->mw->window), &width, &height);
	fontname = get_font_name_from_widget(pub->mw->view);
	ifactory = gtk_item_factory_from_widget(pub->mw->menubar);
	wordwrap = gtk_check_menu_item_get_active(
		GTK_CHECK_MENU_ITEM(gtk_item_factory_get_item(ifactory,
			"/Options/Word Wrap")));
	linenumbers = gtk_check_menu_item_get_active(
		GTK_CHECK_MENU_ITEM(gtk_item_factory_get_item(ifactory,
			"/Options/Line Numbers")));
	autoindent = gtk_check_menu_item_get_active(
		GTK_CHECK_MENU_ITEM(gtk_item_factory_get_item(ifactory,
			"/Options/Auto Indent")));

#if GLIB_CHECK_VERSION(2, 6, 0)
	path = g_build_filename(g_get_user_config_dir(), PACKAGE, NULL);
	if (!g_file_test(path, G_FILE_TEST_IS_DIR)) {
# if GLIB_CHECK_VERSION(2, 8, 0)
		g_mkdir_with_parents(path, 0700);
# else
		g_mkdir(g_get_user_config_dir(), 0700);
		g_mkdir(path, 0700);
# endif
	}
	g_free(path);
	path = g_build_filename(g_get_user_config_dir(),
	    PACKAGE, PACKAGE "rc", NULL);
#else
	path = g_build_filename(g_get_home_dir(), "." PACKAGE, NULL);
#endif
	fp = fopen(path, "w");
	if (!fp) {
		g_print("%s: can't save config file - %s\n", PACKAGE, path);
		return;
	}
	g_free(path);

	fprintf(fp, "%s\n", PACKAGE_VERSION);
	fprintf(fp, "%d\n", width);
	fprintf(fp, "%d\n", height);
	fprintf(fp, "%s\n", fontname);
	fprintf(fp, "%d\n", wordwrap);
	fprintf(fp, "%d\n", linenumbers);
	fprintf(fp, "%d\n", autoindent);
	fclose(fp);

	g_free(fontname);
}
