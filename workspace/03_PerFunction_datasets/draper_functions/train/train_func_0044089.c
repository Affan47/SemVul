brasero_app_indicator_build_menu (BraseroAppIndicator *indicator)
{
	GtkActionGroup *action_group;
	GtkWidget *menu = NULL,
		*menu_item = NULL;
	GError *error = NULL;

	action_group = gtk_action_group_new ("MenuAction");
	gtk_action_group_set_translation_domain (action_group, GETTEXT_PACKAGE);
	gtk_action_group_add_actions (action_group,
				      entries,
				      G_N_ELEMENTS (entries),
				      indicator);
	gtk_action_group_add_toggle_actions (action_group,
					     toggle_entries,
					     G_N_ELEMENTS (toggle_entries),
					     indicator);

	indicator->priv->manager = gtk_ui_manager_new ();
	gtk_ui_manager_insert_action_group (indicator->priv->manager,
					    action_group,
					    0);

	if (!gtk_ui_manager_add_ui_from_string (indicator->priv->manager,
						description,
						-1,
						&error)) {
		g_message ("building menus failed: %s", error->message);
		g_error_free (error);
	} else {
		menu = gtk_ui_manager_get_widget (indicator->priv->manager, "/ContextMenu");
		menu_item = gtk_ui_manager_get_widget (indicator->priv->manager, "/ContextMenu/Progress");
		gtk_widget_set_sensitive (menu_item, FALSE);

		menu_item = gtk_ui_manager_get_widget (indicator->priv->manager, "/ContextMenu/Cancel");
		gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menu_item), GTK_WIDGET (gtk_image_new ()));
	}

	return menu;
}
