nemo_icon_container_receive_dropped_icons (NemoIconContainer *container,
					       GdkDragContext *context,
					       int x, int y)
{
	char *drop_target, *container_uri;
	gboolean local_move_only;
	double world_x, world_y;
	gboolean icon_hit;
	GdkDragAction action, real_action;
	NemoDragSelectionItem *selected_item;

	drop_target = NULL;

	if (container->details->dnd_info->drag_info.selection_list == NULL) {
		return;
	}

	real_action = gdk_drag_context_get_selected_action (context);

	if (real_action == GDK_ACTION_ASK) {


		if (nemo_drag_selection_includes_special_link (container->details->dnd_info->drag_info.selection_list)) {

			action = GDK_ACTION_MOVE;
		} else {
			action = GDK_ACTION_MOVE | GDK_ACTION_COPY | GDK_ACTION_LINK;
		}
		real_action = nemo_drag_drop_action_ask (GTK_WIDGET (container), action);
	}

	if (real_action > 0) {
		eel_canvas_window_to_world (EEL_CANVAS (container),
					    x + gtk_adjustment_get_value (gtk_scrollable_get_hadjustment (GTK_SCROLLABLE (container))),
					    y + gtk_adjustment_get_value (gtk_scrollable_get_vadjustment (GTK_SCROLLABLE (container))),
					    &world_x, &world_y);

		drop_target = nemo_icon_container_find_drop_target (container,
									context, x, y, &icon_hit, FALSE);

		local_move_only = FALSE;
		if (!icon_hit && real_action == GDK_ACTION_MOVE) {


			local_move_only = nemo_icon_container_selection_items_local
				(container, container->details->dnd_info->drag_info.selection_list);
		}

		if (local_move_only) {
			handle_local_move (container, world_x, world_y);
		} else {
			handle_nonlocal_move (container, real_action, world_x, world_y, drop_target, icon_hit);
		}
	}

	g_free (drop_target);
	nemo_drag_destroy_selection_list (container->details->dnd_info->drag_info.selection_list);
	container->details->dnd_info->drag_info.selection_list = NULL;
}
