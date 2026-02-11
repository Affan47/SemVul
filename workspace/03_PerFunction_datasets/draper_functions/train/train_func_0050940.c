brasero_data_project_move_node (BraseroDataProject *self,
				BraseroFileNode *node,
				BraseroFileNode *parent)
{
	BraseroFileNode *imported_sibling;
	BraseroFileNode *target_sibling;
	BraseroDataProjectPrivate *priv;
	BraseroDataProjectClass *klass;
	BraseroFileNode *former_parent;
	BraseroFileTreeStats *stats;
	guint former_position;
	gboolean check_graft;

	priv = BRASERO_DATA_PROJECT_PRIVATE (self);

	if (!parent)
		parent = priv->root;
	else if (parent->is_file || parent->is_loading)
		return FALSE;


	if (node->parent == parent)
		return FALSE;


	if (brasero_file_node_is_ancestor (node, parent))
		return FALSE;


	if (!brasero_data_project_is_deep (self, parent, BRASERO_FILE_NODE_NAME (node), node->is_file))
		return FALSE;


	target_sibling = brasero_file_node_check_name_existence (parent, BRASERO_FILE_NODE_NAME (node));
	if (target_sibling) {
		if (BRASERO_FILE_NODE_VIRTUAL (target_sibling)) {
			brasero_data_project_virtual_sibling (self, node, target_sibling);
			target_sibling = NULL;
		}
		else if (brasero_data_project_node_signal (self, NAME_COLLISION_SIGNAL, target_sibling))
			return FALSE;
	}


	brasero_data_project_joliet_remove_node (self, node);


	if (!target_sibling || !brasero_file_node_is_ancestor (target_sibling, node))
		imported_sibling = brasero_file_node_check_imported_sibling (node);
	else
		imported_sibling = NULL;

	if (!node->is_grafted) {
		gchar *uri;


		uri = brasero_data_project_node_to_uri (self, node);
		if (!g_hash_table_lookup (priv->grafts, uri))
			brasero_data_project_uri_graft_nodes (self, uri);
		g_free (uri);

		check_graft = FALSE;
	}
	else
		check_graft = TRUE;


	former_parent = node->parent;
	former_position = brasero_file_node_get_pos_as_child (node);
	stats = brasero_file_node_get_tree_stats (priv->root, NULL);
	brasero_file_node_move_from (node, stats);

	klass = BRASERO_DATA_PROJECT_GET_CLASS (self);
	if (former_parent && klass->node_removed)
		klass->node_removed (self, former_parent, former_position, node);

	if (target_sibling)
		brasero_data_project_remove_sibling (self,
						     target_sibling,
						     node);

	brasero_file_node_move_to (node, parent, priv->sort_func);

	if (klass->node_added)
		klass->node_added (self, node, NULL);

	if (check_graft) {
		BraseroGraft *graft;
		BraseroURINode *uri_node;

		graft = BRASERO_FILE_NODE_GRAFT (node);
		uri_node = graft->node;


		if (!brasero_data_project_uri_is_graft_needed (self, uri_node->uri))
			brasero_data_project_uri_remove_graft (self, uri_node->uri);
	}


	if (strlen (BRASERO_FILE_NODE_NAME (node)) > 64)
		brasero_data_project_joliet_add_node (self, node);

	if (imported_sibling) {
		BraseroDataProjectClass *klass;

		klass = BRASERO_DATA_PROJECT_GET_CLASS (self);
		brasero_file_node_add (imported_sibling->parent, imported_sibling, priv->sort_func);
		if (klass->node_added)
			brasero_data_project_add_node_and_children (self, imported_sibling, klass->node_added);
	}


	return TRUE;
}
