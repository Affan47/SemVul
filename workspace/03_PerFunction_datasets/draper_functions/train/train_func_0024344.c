compute_drop_position (GtkTreeView *tree_view,
		       int                      x,
		       int                      y,
		       GtkTreePath            **path,
		       GtkTreeViewDropPosition *pos,
		       NemoPlacesSidebar *sidebar)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	PlaceType place_type;
	SectionType section_type;
    gchar *drop_target_uri;

	if (!gtk_tree_view_get_dest_row_at_pos (tree_view,
						x, y,
						path, pos)) {
		return FALSE;
	}
	model = gtk_tree_view_get_model (tree_view);

	gtk_tree_model_get_iter (model, &iter, *path);
	gtk_tree_model_get (model, &iter,
			    PLACES_SIDEBAR_COLUMN_ROW_TYPE, &place_type,
			    PLACES_SIDEBAR_COLUMN_SECTION_TYPE, &section_type,
                PLACES_SIDEBAR_COLUMN_URI, &drop_target_uri,
			    -1);
	if (!cat_is_expanded (sidebar, section_type) && place_type == PLACES_HEADING) {
        if (sidebar->expand_timeout_source > 0) {
            gtk_tree_path_free (*path);
            *path = NULL;
            return FALSE;
        }
        CategoryExpandPayload *payload;
        GtkTreeViewColumn *col;
        col = gtk_tree_view_get_column (GTK_TREE_VIEW (tree_view), 2);
        payload = g_new0 (CategoryExpandPayload, 1);
        payload->sidebar = sidebar;
        gtk_tree_view_get_cell_area (tree_view,
                                     *path,
                                     col,
                                     &payload->rect);
        payload->section_type = section_type;
        sidebar->expand_timeout_source = g_timeout_add_full (G_PRIORITY_DEFAULT,
                                                             DRAG_EXPAND_CATEGORY_DELAY,
                                                             (GSourceFunc) maybe_expand_category,
                                                             payload,
                                                             (GDestroyNotify) g_free);
		gtk_tree_path_free (*path);
		*path = NULL;
		return FALSE;
	} else if (place_type == PLACES_HEADING) {
        gtk_tree_path_free (*path);
        *path = NULL;
        return FALSE;
    }

	if (section_type != SECTION_BOOKMARKS &&
	    sidebar->drag_data_received &&
	    sidebar->drag_data_info == GTK_TREE_MODEL_ROW) {


		gtk_tree_path_free (*path);
		*path = NULL;

		return FALSE;
	}


    GdkRectangle rect;
    GtkTreeViewColumn *col;
    col = gtk_tree_view_get_column (GTK_TREE_VIEW (tree_view), 1);
    gtk_tree_view_get_cell_area (tree_view,
                                     *path,
                                     col,
                                     &rect);

    *pos = get_drag_type (sidebar, drop_target_uri, rect, y, section_type);

	if (*pos != GTK_TREE_VIEW_DROP_BEFORE &&
	    sidebar->drag_data_received &&
	    sidebar->drag_data_info == GTK_TREE_MODEL_ROW) {

		*pos = GTK_TREE_VIEW_DROP_AFTER;
	}

	return TRUE;
}
