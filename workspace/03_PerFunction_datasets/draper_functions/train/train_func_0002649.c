add_main_window_contents (GtkWidget *window, GtkWidget *notebook)
{
	GtkWidget *box1, *recent_menu;
	GtkActionGroup *actions;
	GError *error = NULL;
	GtkAction *act;

	stock_init ();

	actions = gtk_action_group_new ("Actions");
	gtk_action_group_set_translation_domain (actions, GETTEXT_PACKAGE);
	gtk_action_group_add_actions (actions, entries, n_entries, NULL);


	act = gtk_action_group_get_action (actions, "Interrupt");
	gtk_action_set_is_important (act, TRUE);
	act = gtk_action_group_get_action (actions, "Run");
	gtk_action_set_is_important (act, TRUE);
	act = gtk_action_group_get_action (actions, "ToolbarNew");
	gtk_action_set_is_important (act, TRUE);
	act = gtk_action_group_get_action (actions, "ToolbarOpen");
	gtk_action_set_is_important (act, TRUE);
	act = gtk_action_group_get_action (actions, "ToolbarPlot");
	gtk_action_set_is_important (act, TRUE);
	act = gtk_action_group_get_action (actions, "Quit");
	gtk_action_set_is_important (act, TRUE);

	genius_ui = gtk_ui_manager_new ();
	genius_window_statusbar = gtk_statusbar_new ();
	g_signal_connect (genius_ui, "connect_proxy",
			  G_CALLBACK (connect_proxy_cb), genius_window_statusbar);
	g_signal_connect (genius_ui, "disconnect_proxy",
			  G_CALLBACK (disconnect_proxy_cb), genius_window_statusbar);

	gtk_ui_manager_insert_action_group (genius_ui, actions, 0);
	g_object_unref (actions);
	gtk_window_add_accel_group (GTK_WINDOW (window),
				    gtk_ui_manager_get_accel_group (genius_ui));
	gtk_container_set_border_width (GTK_CONTAINER (window), 0);

	if ( ! gtk_ui_manager_add_ui_from_string (genius_ui, ui_info, -1, &error)) {

		g_message ("building menus failed: %s", error->message);
		g_error_free (error);
	}

	box1 = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), box1);

	gtk_box_pack_start (GTK_BOX (box1),
			    gtk_ui_manager_get_widget (genius_ui, "/MenuBar"),
			    FALSE, FALSE, 0);

	gtk_box_pack_start (GTK_BOX (box1),
			    gtk_ui_manager_get_widget (genius_ui, "/ToolBar"),
			    FALSE, FALSE, 0);

	gtk_box_pack_start (GTK_BOX (box1), notebook, TRUE, TRUE, 0);

	gtk_statusbar_set_has_resize_grip (GTK_STATUSBAR (genius_window_statusbar), TRUE);
	gtk_box_pack_start (GTK_BOX (box1), genius_window_statusbar, FALSE, TRUE, 0);

        recent_menu  = recent_create_menu ();
	g_signal_connect (G_OBJECT (recent_menu), "item-activated",
			  G_CALLBACK (file_open_recent), NULL);
	gtk_menu_item_set_submenu
		(GTK_MENU_ITEM (gtk_ui_manager_get_widget (genius_ui, "/MenuBar/FileMenu/OpenRecent")),
		 recent_menu);

}
