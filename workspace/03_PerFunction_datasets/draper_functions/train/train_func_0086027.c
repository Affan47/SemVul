plugin_cleanup(void)
{
	gtk_widget_destroy(sc_info->edit_menu);
	gtk_widget_destroy(sc_info->edit_menu_sep);
	if (sc_info->toolbar_button != NULL)
		gtk_widget_destroy(GTK_WIDGET(sc_info->toolbar_button));

	sc_gui_free();
	sc_speller_free();

	g_free(sc_info->dictionary_dir);
	g_free(sc_info->default_language);
	g_free(sc_info->config_file);
	gtk_widget_destroy(sc_info->menu_item);
	g_free(sc_info);
}
