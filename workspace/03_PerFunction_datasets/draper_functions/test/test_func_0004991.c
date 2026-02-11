nemo_list_model_multi_drag_data_get (EggTreeMultiDragSource *drag_source,
					 GList *path_list,
					 GtkSelectionData *selection_data)
{
	NemoListModel *model;
	DragDataGetInfo context;
	guint target_info;

	model = NEMO_LIST_MODEL (drag_source);

	context.model = model;
	context.path_list = path_list;

	if (!drag_target_list) {
		drag_target_list = nemo_list_model_get_drag_target_list ();
	}

	if (gtk_target_list_find (drag_target_list,
				  gtk_selection_data_get_target (selection_data),
				  &target_info)) {
		nemo_drag_drag_data_get (NULL,
					     NULL,
					     selection_data,
					     target_info,
					     GDK_CURRENT_TIME,
					     &context,
					     each_path_get_data_binder);
		return TRUE;
	} else {
		return FALSE;
	}
}
