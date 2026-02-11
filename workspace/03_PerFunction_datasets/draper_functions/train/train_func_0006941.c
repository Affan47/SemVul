nautilus_canvas_view_merge_menus (NautilusView *view)
{
	NautilusCanvasView *canvas_view;
	GtkUIManager *ui_manager;
	GtkActionGroup *action_group;

        g_assert (NAUTILUS_IS_CANVAS_VIEW (view));

	NAUTILUS_VIEW_CLASS (nautilus_canvas_view_parent_class)->merge_menus (view);

	canvas_view = NAUTILUS_CANVAS_VIEW (view);

	ui_manager = nautilus_view_get_ui_manager (NAUTILUS_VIEW (canvas_view));

	action_group = gtk_action_group_new ("CanvasViewActions");
	gtk_action_group_set_translation_domain (action_group, GETTEXT_PACKAGE);
	canvas_view->details->canvas_action_group = action_group;
	gtk_action_group_add_toggle_actions (action_group,
					     canvas_view_toggle_entries, G_N_ELEMENTS (canvas_view_toggle_entries),
					     canvas_view);
	gtk_action_group_add_radio_actions (action_group,
					    arrange_radio_entries,
					    G_N_ELEMENTS (arrange_radio_entries),
					    -1,
					    G_CALLBACK (action_sort_radio_callback),
					    canvas_view);

	gtk_ui_manager_insert_action_group (ui_manager, action_group, 0);
	g_object_unref (action_group);

	canvas_view->details->canvas_merge_id =
		gtk_ui_manager_add_ui_from_resource (ui_manager, "/org/gnome/nautilus/nautilus-canvas-view-ui.xml", NULL);

	update_layout_menus (canvas_view);
}
