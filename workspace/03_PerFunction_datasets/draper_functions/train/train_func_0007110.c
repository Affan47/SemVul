rb_tree_dnd_drag_drop_cb (GtkWidget        *widget,
                         GdkDragContext   *context,
                         gint              x,
                         gint              y,
                         guint             time)
{
	GtkTreeView *tree_view;
	GtkTreePath *path;
	GtkTreeModel *model;
	GtkTreeViewDropPosition pos;
	RbTreeDndData *priv_data;

	tree_view = GTK_TREE_VIEW (widget);
	model = gtk_tree_view_get_model (tree_view);
	priv_data = g_object_get_data (G_OBJECT (widget), RB_TREE_DND_STRING);
	gtk_tree_view_get_dest_row_at_pos (tree_view, x, y, &path, &pos);

	remove_scroll_timeout (tree_view);


	gtk_tree_view_set_drag_dest_row (tree_view,
               				 NULL,
					 GTK_TREE_VIEW_DROP_BEFORE);

	if (path || priv_data->dest_flags & RB_TREE_DEST_EMPTY_VIEW_DROP) {

		GdkAtom target;
		RbTreeDragDestIface *iface = RB_TREE_DRAG_DEST_GET_IFACE (model);
		if (iface->rb_get_drag_target) {
			RbTreeDragDest *dest = RB_TREE_DRAG_DEST (model);
			target = (* iface->rb_get_drag_target) (dest, widget,
								context, path,
								priv_data->dest_target_list);
		} else {
			target = gtk_drag_dest_find_target (widget, context,
							    priv_data->dest_target_list);
		}

		if (path)
			gtk_tree_path_free (path);

		if (target != GDK_NONE) {
			gtk_drag_get_data (widget, context, target, time);
			return TRUE;
		}
	}

	return FALSE;
}
