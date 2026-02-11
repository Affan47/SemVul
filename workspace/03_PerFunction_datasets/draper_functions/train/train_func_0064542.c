git_branches_pane_init (GitBranchesPane *self)
{
	gchar *objects[] = {"branches_pane",
						"branches_list_model",
						NULL};
	GError *error = NULL;
	GtkTreeView *branches_view;
	GtkTreeViewColumn *branch_selected_column;
	GtkCellRenderer *branch_selected_renderer;
	GtkTreeViewColumn *branch_name_column;
	GtkCellRenderer *branch_active_icon_renderer;

	self->priv = g_new0 (GitBranchesPanePriv, 1);
	self->priv->builder = gtk_builder_new ();
	self->priv->selected_local_branches = g_hash_table_new_full (g_str_hash,
	                                                             g_str_equal,
	                                                             g_free,
	                                                             NULL);
	self->priv->selected_remote_branches = g_hash_table_new_full (g_str_hash,
	                                                              g_str_equal,
	                                                              g_free,
	                                                              NULL);


	if (!gtk_builder_add_objects_from_file (self->priv->builder, BUILDER_FILE,
	                                        objects,
	                                        &error))
	{
		g_warning ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	branches_view = GTK_TREE_VIEW (gtk_builder_get_object (self->priv->builder,
	                                                       "branches_view"));
	branch_selected_column = GTK_TREE_VIEW_COLUMN (gtk_builder_get_object (self->priv->builder,
	                                               "branch_selected_column"));
	branch_selected_renderer = GTK_CELL_RENDERER (gtk_builder_get_object (self->priv->builder,
	                                              "branch_selected_renderer"));
	branch_name_column = GTK_TREE_VIEW_COLUMN (gtk_builder_get_object (self->priv->builder,
	                                           "branch_name_column"));
	branch_active_icon_renderer = GTK_CELL_RENDERER (gtk_builder_get_object (self->priv->builder,
	                                                                         "branch_active_icon_renderer"));


	gtk_tree_view_enable_model_drag_source (branches_view,
	                                        GDK_BUTTON1_MASK,
	                                        drag_targets,
	                                        G_N_ELEMENTS (drag_targets),
	                                        GDK_ACTION_COPY);

	g_signal_connect (G_OBJECT (branches_view), "drag-data-get",
	                  G_CALLBACK (on_branches_list_view_drag_data_get),
	                  self);

	gtk_tree_view_column_set_cell_data_func (branch_selected_column,
	                                         branch_selected_renderer,
	                                         (GtkTreeCellDataFunc) selected_column_data_func,
	                                         self,
	                                         NULL);

	gtk_tree_view_column_set_cell_data_func (branch_name_column,
	                                         branch_active_icon_renderer,
	                                         (GtkTreeCellDataFunc) active_icon_data_func,
	                                         self,
	                                         NULL);

	g_signal_connect (G_OBJECT (branch_selected_renderer), "toggled",
	                  G_CALLBACK (on_branch_selected_renderer_toggled),
	                  self);


	g_signal_connect (G_OBJECT (branches_view), "row-activated",
	                  G_CALLBACK (on_branches_view_row_activated),
	                  self);


	g_signal_connect (G_OBJECT (branches_view), "button-press-event",
	                  G_CALLBACK (on_branches_view_button_press_event),
	                  self);
}
