get_main_menu(GtkWidget *window, GtkWidget **menubar,
	GtkWidget *menubox)
{
	GError *error = NULL;
	guint n_action_items;
	GtkActionGroup *action_group;
	GtkAccelGroup *accel_group;

	main_menu_xml = g_strdup("");
	main_menu_xml = g_strconcat("<ui>\
			<menubar>\
				<menu name=\"Chat\" action=\"Chat\">\
					<menu name=\"Set status\" action=\"Set status\"/>\
					<menuitem action=\"SignonAll\"/>\
					<menuitem action=\"SignoffAll\"/>\
					<separator/>\
					<menuitem action=\"GrpChat\"/>\
					<menuitem action=\"SetAway\"/>\
					<separator/>\
					<menu name=\"Smileys\" action=\"Smileys\"/>\
					<separator/>\
					<menuitem action=\"Quit\"/>\
				</menu>\
				<menu name=\"Edit\" action=\"Edit\">\
					<menuitem action=\"Prefs\"/>\
					<menuitem action=\"AddDelAccounts\"/>\
					<menuitem action=\"EditAccounts\"/>\
					<separator/>\
					<menuitem action=\"AddContactAccount\"/>\
					<menuitem action=\"AddGroup\"/>\
					<separator/>\
					<menu name=\"Import\" action=\"Import\"/>\
					<menu name=\"Set profile\" action=\"Set profile\"/>\
				</menu>\
				<menu name=\"Help\" action=\"Help\">",
#ifndef __MINGW32__
		"<menuitem action=\"Website\"/>\
					<menuitem action=\"Manual\"/>\
					<separator/>",
#endif
		"<menuitem name=\"About\" action=\"About\"/>\
					<separator/>\
					<menuitem action=\"CheckRelease\"/>",
#if ADD_DEBUG_TO_MENU
		"<separator/>\
					<menuitem action=\"DebugMenu\"/>",
#endif
		"</menu>\
			</menubar>\
		</ui>", NULL);

	n_action_items = G_N_ELEMENTS(action_items);

	action_group = gtk_action_group_new("MainMenuActions");
	gtk_action_group_add_actions(action_group, action_items, n_action_items,
		NULL);
	gtk_action_group_set_translate_func(action_group, menu_translate, NULL,
		NULL);
	ui_manager = gtk_ui_manager_new();
	gtk_ui_manager_insert_action_group(ui_manager, action_group, 0);
	gtk_ui_manager_add_ui_from_string(ui_manager, main_menu_xml, -1,
		&error);
	if (error) {
		eb_debug(DBG_CORE, "Failed to build main menu: %s\n",
			error->message);
		exit(1);
	}

	g_signal_connect(ui_manager, "add-widget", G_CALLBACK(menu_add_widget),
		menubox);
	*menubar = gtk_ui_manager_get_widget(ui_manager, "ui/menubar");
	if ((accel_group = gtk_ui_manager_get_accel_group(ui_manager)))
		gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);
	else
		eb_debug(DBG_CORE,
			"WARNING: No Accel Group returned by UIManager\n");
}
