brasero_file_node_set_from_info (BraseroFileNode *node,
				 BraseroFileTreeStats *stats,
				 GFileInfo *info)
{


	if (node->parent) {


		if (!node->is_file && (g_file_info_get_file_type (info) != G_FILE_TYPE_DIRECTORY)) {
			stats->children ++;
			stats->num_dir --;
		}
		else if (node->is_file && (g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY)) {
			stats->children --;
			stats->num_dir ++;
		}
	}

	if (!node->is_symlink
	&& (g_file_info_get_file_type (info) == G_FILE_TYPE_SYMBOLIC_LINK)) {

		stats->num_sym ++;
	}


	node->is_file = (g_file_info_get_file_type (info) != G_FILE_TYPE_DIRECTORY);
	node->is_fake = FALSE;
	node->is_loading = FALSE;
	node->is_imported = FALSE;
	node->is_reloading = FALSE;
	node->is_symlink = (g_file_info_get_file_type (info) == G_FILE_TYPE_SYMBOLIC_LINK);

	if (node->is_file) {
		guint sectors;
		gint sectors_diff;


		if (g_file_info_has_attribute (info, G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE)) {
			const gchar *mime;

			if (BRASERO_FILE_NODE_MIME (node))
				brasero_utils_unregister_string (BRASERO_FILE_NODE_MIME (node));

			mime = g_file_info_get_content_type (info);
			node->union2.mime = brasero_utils_register_string (mime);
		}

		sectors = BRASERO_BYTES_TO_SECTORS (g_file_info_get_size (info), 2048);

		if (sectors > BRASERO_FILE_2G_LIMIT && BRASERO_FILE_NODE_SECTORS (node) <= BRASERO_FILE_2G_LIMIT) {
			node->is_2GiB = 1;
			stats->num_2GiB ++;
		}
		else if (sectors <= BRASERO_FILE_2G_LIMIT && BRASERO_FILE_NODE_SECTORS (node) > BRASERO_FILE_2G_LIMIT) {
			node->is_2GiB = 0;
			stats->num_2GiB --;
		}


		sectors_diff = sectors - BRASERO_FILE_NODE_SECTORS (node);
		for (; node; node = node->parent) {
			node->union3.sectors += sectors_diff;
			if (node->is_grafted)
				break;
		}
	}
	else
		node->is_exploring = TRUE;
}
