rb_tree_dnd_add_drag_dest_support (GtkTreeView *tree_view,
				   RbTreeDestFlag flags,
				   const GtkTargetEntry *targets,
				   gint n_targets,
				   GdkDragAction actions)
{
	RbTreeDndData *priv_data = NULL;
	g_return_if_fail (GTK_IS_TREE_VIEW (tree_view));

	priv_data = init_rb_tree_dnd_data (GTK_WIDGET(tree_view));

	if (!priv_data->drag_motion_handler) {

		priv_data->dest_target_list = gtk_target_list_new (targets, n_targets);
		priv_data->dest_actions = actions;
		priv_data->dest_flags = flags;

		gtk_drag_dest_set (GTK_WIDGET (tree_view),
				   0,
				   NULL,
				   0,
				   actions);

		priv_data->drag_motion_handler = g_signal_connect (G_OBJECT (tree_view),
								  "drag_motion",
								  G_CALLBACK (rb_tree_dnd_drag_motion_cb),
								  NULL);
		priv_data->drag_leave_handler = g_signal_connect (G_OBJECT (tree_view),
								  "drag_leave",
								  G_CALLBACK (rb_tree_dnd_drag_leave_cb),
								  NULL);
		priv_data->drag_drop_handler = g_signal_connect (G_OBJECT (tree_view),
								 "drag_drop",
								 G_CALLBACK (rb_tree_dnd_drag_drop_cb),
								 NULL);
	  	priv_data->drag_data_received_handler = g_signal_connect (G_OBJECT (tree_view),
									  "drag_data_received",
									  G_CALLBACK (rb_tree_dnd_drag_data_received_cb),
									  NULL);
	}
}
