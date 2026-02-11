status_name_renderer_data_func (GtkTreeViewColumn *tree_column,
                                GtkCellRenderer *renderer,
                                GtkTreeModel *model,
                                GtkTreeIter *iter,
                                gpointer user_data)
{
	AnjutaVcsStatus status;

	gtk_tree_model_get (model, iter, COL_STATUS, &status, -1);


	gtk_cell_renderer_set_visible (renderer,
	                               gtk_tree_store_iter_depth (GTK_TREE_STORE (model),
	                                                          iter) == 1);

	switch (status)
	{
		case ANJUTA_VCS_STATUS_MODIFIED:
			g_object_set (G_OBJECT (renderer), "text", _("Modified"), NULL);
			break;
		case ANJUTA_VCS_STATUS_ADDED:
			g_object_set (G_OBJECT (renderer), "text", _("Added"), NULL);
			break;
		case ANJUTA_VCS_STATUS_DELETED:
			g_object_set (G_OBJECT (renderer), "text", _("Deleted"), NULL);
			break;
		case ANJUTA_VCS_STATUS_CONFLICTED:
			g_object_set (G_OBJECT (renderer), "text", _("Conflicted"),
									NULL);
			break;
		case ANJUTA_VCS_STATUS_UPTODATE:
			g_object_set (G_OBJECT (renderer), "text", _("Up-to-date"),
						  NULL);
			break;
		case ANJUTA_VCS_STATUS_LOCKED:
			g_object_set (G_OBJECT (renderer), "text", _("Locked"), NULL);
			break;
		case ANJUTA_VCS_STATUS_MISSING:
			g_object_set (G_OBJECT (renderer), "text", _("Missing"), NULL);
			break;
		case ANJUTA_VCS_STATUS_UNVERSIONED:
			g_object_set (G_OBJECT (renderer), "text", _("Unversioned"),
									NULL);
			break;
		case ANJUTA_VCS_STATUS_IGNORED:
			g_object_set (G_OBJECT (renderer), "text", _("Ignored"),
						  NULL);
			break;
		case ANJUTA_VCS_STATUS_NONE:
		default:
			break;
	}
}
