brasero_data_project_add_imported_session_file (BraseroDataProject *self,
						GFileInfo *info,
						BraseroFileNode *parent)
{
	BraseroFileNode *node;
	BraseroFileNode *sibling;
	BraseroDataProjectClass *klass;
	BraseroDataProjectPrivate *priv;

	g_return_val_if_fail (BRASERO_IS_DATA_PROJECT (self), NULL);
	g_return_val_if_fail (info != NULL, NULL);

	priv = BRASERO_DATA_PROJECT_PRIVATE (self);

	if (!parent)
		parent = priv->root;

	sibling = brasero_file_node_check_name_existence (parent, g_file_info_get_name (info));
	if (sibling) {


		if (BRASERO_FILE_NODE_VIRTUAL (sibling)) {
			node = brasero_file_node_new_imported_session_file (info);
			brasero_data_project_virtual_sibling (self, node, sibling);
		}
		else if (sibling->is_fake && sibling->is_tmp_parent) {
			BraseroGraft *graft;
			BraseroURINode *uri_node;

			graft = BRASERO_FILE_NODE_GRAFT (sibling);
			uri_node = graft->node;


			brasero_file_node_ungraft (sibling);


			if (!uri_node->nodes
			&&  !brasero_data_project_uri_has_parent (self, uri_node->uri))
				brasero_data_project_uri_remove_graft (self, uri_node->uri);

			if (sibling->is_file)
				sibling->is_fake = FALSE;
			else
				sibling->union3.imported_address = g_file_info_get_attribute_int64 (info, BRASERO_IO_DIR_CONTENTS_ADDR);

			sibling->is_imported = TRUE;
			sibling->is_tmp_parent = FALSE;


			klass = BRASERO_DATA_PROJECT_GET_CLASS (self);
			if (klass->node_changed)
				klass->node_changed (self, sibling);

			return sibling;
		}
		else if (brasero_data_project_node_signal (self, NAME_COLLISION_SIGNAL, sibling))
			return NULL;
		else {


			brasero_data_project_remove_real (self, sibling);
			node = brasero_file_node_new_imported_session_file (info);
		}
	}
	else
		node = brasero_file_node_new_imported_session_file (info);


	brasero_file_node_add (parent, node, priv->sort_func);


	klass = BRASERO_DATA_PROJECT_GET_CLASS (self);
	if (klass->node_added)
		klass->node_added (self, node, NULL);

	return node;
}
