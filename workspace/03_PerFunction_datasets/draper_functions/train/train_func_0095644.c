brasero_track_data_cfg_node_to_path (BraseroTrackDataCfg *self,
				     BraseroFileNode *node)
{
	GtkTreePath *path;

	path = gtk_tree_path_new ();
	for (; node->parent && !node->is_root; node = node->parent) {
		guint nth;

		nth = brasero_track_data_cfg_get_pos_as_child (node);
		gtk_tree_path_prepend_index (path, nth);
	}

	return path;
}
