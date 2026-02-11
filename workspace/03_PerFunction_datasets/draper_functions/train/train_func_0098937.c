et_build_groups (ETable *et)
{
	gboolean was_grouped = et->is_grouped;

	et->is_grouped = e_table_sort_info_grouping_get_count (et->sort_info) > 0;

	et->group = e_table_group_new (
		GNOME_CANVAS_GROUP (et->canvas_vbox),
		et->full_header,
		et->header,
		et->model,
		et->sort_info,
		0);

	if (et->use_click_to_add_end)
		e_canvas_vbox_add_item_start (
			E_CANVAS_VBOX (et->canvas_vbox),
			GNOME_CANVAS_ITEM (et->group));
	else
		e_canvas_vbox_add_item (
			E_CANVAS_VBOX (et->canvas_vbox),
			GNOME_CANVAS_ITEM (et->group));

	gnome_canvas_item_set (
		GNOME_CANVAS_ITEM (et->group),
		"alternating_row_colors", et->alternating_row_colors,
		"horizontal_draw_grid", et->horizontal_draw_grid,
		"vertical_draw_grid", et->vertical_draw_grid,
		"drawfocus", et->draw_focus,
		"cursor_mode", et->cursor_mode,
		"length_threshold", et->length_threshold,
		"uniform_row_height", et->uniform_row_height,
		"selection_model", et->selection,
		NULL);

	g_signal_connect (
		et->group, "cursor_change",
		G_CALLBACK (group_cursor_change), et);
	g_signal_connect (
		et->group, "cursor_activated",
		G_CALLBACK (group_cursor_activated), et);
	g_signal_connect (
		et->group, "double_click",
		G_CALLBACK (group_double_click), et);
	g_signal_connect (
		et->group, "right_click",
		G_CALLBACK (group_right_click), et);
	g_signal_connect (
		et->group, "click",
		G_CALLBACK (group_click), et);
	g_signal_connect (
		et->group, "key_press",
		G_CALLBACK (group_key_press), et);
	g_signal_connect (
		et->group, "start_drag",
		G_CALLBACK (group_start_drag), et);
	g_signal_connect (
		et->group, "notify::is-editing",
		G_CALLBACK (group_is_editing_changed_cb), et);

	if (!(et->is_grouped) && was_grouped)
		et_disconnect_model (et);

	if (et->is_grouped && (!was_grouped)) {
		et->table_model_change_id = g_signal_connect (
			et->model, "model_changed",
			G_CALLBACK (et_table_model_changed), et);

		et->table_row_change_id = g_signal_connect (
			et->model, "model_row_changed",
			G_CALLBACK (et_table_row_changed), et);

		et->table_cell_change_id = g_signal_connect (
			et->model, "model_cell_changed",
			G_CALLBACK (et_table_cell_changed), et);

		et->table_rows_inserted_id = g_signal_connect (
			et->model, "model_rows_inserted",
			G_CALLBACK (et_table_rows_inserted), et);

		et->table_rows_deleted_id = g_signal_connect (
			et->model, "model_rows_deleted",
			G_CALLBACK (et_table_rows_deleted), et);

	}

	if (et->is_grouped)
		e_table_fill_table (et, et->model);
}
