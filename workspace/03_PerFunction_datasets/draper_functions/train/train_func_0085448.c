plugin_db_disk_get_nb_db_folders ( GWDBContext *context, GWDBDiskPK ref) {
	GNode *disk = ref;
	glong count = 0;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		nb = g_node_n_children ( disk);
		for ( i = 0; i < nb; i++) {
			g_node_traverse ( g_node_nth_child ( disk, i), G_LEVEL_ORDER, G_TRAVERSE_ALL, -1, (GNodeTraverseFunc)g_node_count_folders, &count);
		}
	}

	return count;
}
