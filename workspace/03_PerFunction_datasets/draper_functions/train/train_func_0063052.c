init_toolbar(void)
{
	GtkWidget *toolbar = NULL;

	box = ui_lookup_widget(geany->main_widgets->window, "vbox1");
	uim = gtk_ui_manager_new();
	group = gtk_action_group_new("glatex_format_toolbar");
	gtk_action_group_set_translation_domain(group, GETTEXT_PACKAGE);
	gtk_action_group_add_actions(group, format_icons, ui_entries_n, NULL);
	gtk_ui_manager_insert_action_group(uim, group, 0);
	if (gtk_ui_manager_add_ui_from_string(uim, toolbar_markup, -1, NULL) > 0)
	{
		toolbar = gtk_ui_manager_get_widget(uim, "/ui/glatex_format_toolbar");
		gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(toolbar), FALSE, TRUE, 0);
		gtk_box_reorder_child(GTK_BOX(box), toolbar, 2);
	}


	return toolbar;
}
