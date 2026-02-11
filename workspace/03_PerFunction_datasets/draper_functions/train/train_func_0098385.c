nemo_icon_view_merge_menus (NemoView *view)
{
	NemoIconView *icon_view;
	GtkUIManager *ui_manager;
	GtkActionGroup *action_group;
	GtkAction *action;

        g_assert (NEMO_IS_ICON_VIEW (view));

	NEMO_VIEW_CLASS (nemo_icon_view_parent_class)->merge_menus (view);

	icon_view = NEMO_ICON_VIEW (view);

	ui_manager = nemo_view_get_ui_manager (NEMO_VIEW (icon_view));

	action_group = gtk_action_group_new ("IconViewActions");
	gtk_action_group_set_translation_domain (action_group, GETTEXT_PACKAGE);
	icon_view->details->icon_action_group = action_group;
	gtk_action_group_add_actions (action_group,
				      icon_view_entries, G_N_ELEMENTS (icon_view_entries),
				      icon_view);
	gtk_action_group_add_toggle_actions (action_group,
					     icon_view_toggle_entries, G_N_ELEMENTS (icon_view_toggle_entries),
					     icon_view);
	gtk_action_group_add_radio_actions (action_group,
					    arrange_radio_entries,
					    G_N_ELEMENTS (arrange_radio_entries),
					    -1,
					    G_CALLBACK (action_sort_radio_callback),
					    icon_view);

	gtk_ui_manager_insert_action_group (ui_manager, action_group, 0);
	g_object_unref (action_group);

	icon_view->details->icon_merge_id =
		gtk_ui_manager_add_ui_from_resource (ui_manager, "/org/nemo/nemo-icon-view-ui.xml", NULL);


	if (!nemo_icon_view_supports_auto_layout (icon_view)) {
		action = gtk_action_group_get_action (action_group,
						      NEMO_ACTION_ARRANGE_ITEMS);
		gtk_action_set_visible (action, FALSE);
	}

	if (nemo_icon_view_supports_scaling (icon_view)) {
		gtk_ui_manager_add_ui (ui_manager,
				       icon_view->details->icon_merge_id,
				       POPUP_PATH_ICON_APPEARANCE,
				       NEMO_ACTION_STRETCH,
				       NEMO_ACTION_STRETCH,
				       GTK_UI_MANAGER_MENUITEM,
				       FALSE);
		gtk_ui_manager_add_ui (ui_manager,
				       icon_view->details->icon_merge_id,
				       POPUP_PATH_ICON_APPEARANCE,
				       NEMO_ACTION_UNSTRETCH,
				       NEMO_ACTION_UNSTRETCH,
				       GTK_UI_MANAGER_MENUITEM,
				       FALSE);
	}

	update_layout_menus (icon_view);
}
