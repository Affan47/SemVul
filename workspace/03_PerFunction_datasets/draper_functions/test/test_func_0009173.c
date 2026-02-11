gm_world_paste_dialog_fill_to() {
	GtkWidget *widget = gm_world_paste_dialog_widget("combo_box_to");
	GmWorldView *view = gm_app_view_active_world_view(
			gm_world_paste_dialog_instance->view);
	GtkWidget *paned = GTK_WIDGET(gm_world_view_hpaned(view));
	GtkWidget *tree_view = gm_find_child(paned, GTK_TYPE_TREE_VIEW);
	GtkTreeModel *model;
	GtkTreeModel *sorted;

	if (gm_world_paste_dialog_instance->model != NULL) {
		g_object_ref(gm_world_paste_dialog_instance->model);
		g_object_remove_toggle_ref(
				G_OBJECT(gm_world_paste_dialog_instance->model),
				gm_world_paste_dialog_remove_model, NULL);
	}

	gtk_combo_box_set_model(GTK_COMBO_BOX(widget), NULL);

	if (tree_view == NULL) {
		gm_world_paste_dialog_instance->model = NULL;
		return;
	}

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));

	if (GTK_IS_TREE_MODEL_SORT(model)) {
		model = gtk_tree_model_sort_get_model(GTK_TREE_MODEL_SORT(model));
	}

	g_object_add_toggle_ref(G_OBJECT(model), gm_world_paste_dialog_remove_model,
		NULL);
	g_object_unref(G_OBJECT(model));
	gm_world_paste_dialog_instance->model = model;

	sorted = gtk_tree_model_sort_new_with_model(model);
	gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(sorted),
			GM_USERLIST_NAME, GTK_SORT_ASCENDING);

	gtk_combo_box_set_model(GTK_COMBO_BOX(widget), sorted);

	if (gtk_combo_box_entry_get_text_column(
			GTK_COMBO_BOX_ENTRY(widget)) == -1) {
		gtk_combo_box_entry_set_text_column(GTK_COMBO_BOX_ENTRY(widget),
				GM_USERLIST_NAME);
	}
}
