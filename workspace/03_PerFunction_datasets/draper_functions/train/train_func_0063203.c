panel_menu_items_append_lock_logout (GtkWidget *menu)
{
	GList      *children;
	GList      *last;
	GtkWidget  *item;

	children = gtk_container_get_children (GTK_CONTAINER (menu));
	last = g_list_last (children);
	if (last != NULL &&
	    GTK_IS_SEPARATOR (last->data))
		item = GTK_WIDGET (last->data);
	else
		item = add_menu_separator (menu);
	g_list_free (children);

	panel_lockdown_on_notify (panel_lockdown_get (),
				  NULL,
				  G_OBJECT (item),
				  panel_menu_items_lock_logout_separator_notified,
				  item);
	panel_menu_items_lock_logout_separator_notified (panel_lockdown_get (),
							 item);

	item = panel_menu_items_create_switch_user (FALSE);

	if (item != NULL) {
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
		g_object_bind_property (panel_lockdown_get (),
					"disable-switch-user",
					item,
					"visible",
					G_BINDING_SYNC_CREATE|G_BINDING_INVERT_BOOLEAN);
	}

	item = panel_menu_items_create_action_item_full (PANEL_ACTION_LOGOUT,
							 NULL, NULL, TRUE);

	if (item != NULL) {
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
		g_object_bind_property (panel_lockdown_get (),
					"disable-log-out",
					item,
					"visible",
					G_BINDING_SYNC_CREATE|G_BINDING_INVERT_BOOLEAN);
	}

	item = panel_menu_items_create_action_item_full (PANEL_ACTION_LOCK,
							 NULL, NULL, TRUE);
	if (item != NULL) {
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
		g_object_bind_property (panel_lockdown_get (),
					"disable-lock-screen",
					item,
					"visible",
					G_BINDING_SYNC_CREATE|G_BINDING_INVERT_BOOLEAN);
	}


	if (panel_session_manager_is_shutdown_available (panel_session_manager_get ())) {
		item = panel_menu_items_create_action_item_full (PANEL_ACTION_SHUTDOWN,
								 NULL, NULL, TRUE);
		if (item != NULL) {
			GtkWidget *sep;

			sep = add_menu_separator (menu);

			gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

			g_object_bind_property (panel_lockdown_get (),
						"disable-log-out",
						sep,
						"visible",
						G_BINDING_SYNC_CREATE|G_BINDING_INVERT_BOOLEAN);
			g_object_bind_property (panel_lockdown_get (),
						"disable-log-out",
						item,
						"visible",
						G_BINDING_SYNC_CREATE|G_BINDING_INVERT_BOOLEAN);
		}
	}
}
