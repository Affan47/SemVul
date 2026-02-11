gda_tree_mgr_schemas_update_children (GdaTreeManager *manager, GdaTreeNode *node,
				      G_GNUC_UNUSED const GSList *children_nodes, gboolean *out_error,
				      GError **error)
{
	GdaTreeMgrSchemas *mgr = GDA_TREE_MGR_SCHEMAS (manager);
	GdaMetaStore *store;
	GdaDataModel *model;
	GSList *list = NULL;
	GdaConnection *scnc;

	if (!mgr->priv->cnc && !mgr->priv->mstore) {
		g_set_error (error, GDA_TREE_MANAGER_ERROR, GDA_TREE_MANAGER_UNKNOWN_ERROR,
			     "%s", _("No connection and no GdaMetaStore specified"));
		if (out_error)
			*out_error = TRUE;
		return NULL;
	}
	else if (mgr->priv->mstore)
		store = mgr->priv->mstore;
	else
		store = gda_connection_get_meta_store (mgr->priv->cnc);

	scnc = gda_meta_store_get_internal_connection (store);

	if (!mgr->priv->stmt) {
		GdaSqlParser *parser;
		GdaStatement *stmt;

		parser = gda_connection_create_parser (scnc);
		if (! parser)
			parser = gda_sql_parser_new ();

		stmt = gda_sql_parser_parse_string (parser,
						    "SELECT schema_name FROM _schemata "
						    "WHERE schema_internal = FALSE OR schema_name LIKE 'info%' "
						    "ORDER BY schema_name DESC", NULL, error);
		g_object_unref (parser);
		if (!stmt) {
			if (out_error)
				*out_error = TRUE;
			return NULL;
		}
		mgr->priv->stmt = stmt;
	}

	model = gda_connection_statement_execute_select (scnc, mgr->priv->stmt, NULL, error);
	if (!model) {
		if (out_error)
			*out_error = TRUE;
		return NULL;
	}

	GdaDataModelIter *iter;
	iter = gda_data_model_create_iter (model);
	for (; iter && gda_data_model_iter_move_next (iter);) {
		GdaTreeNode* snode;
		const GValue *cvalue;

		cvalue = gda_data_model_iter_get_value_at (iter, 0);
		if (!cvalue) {
			if (list) {
				g_slist_foreach (list, (GFunc) g_object_unref, NULL);
				g_slist_free (list);
			}
			if (out_error)
				*out_error = TRUE;
			g_set_error (error, GDA_TREE_MANAGER_ERROR, GDA_TREE_MANAGER_UNKNOWN_ERROR,
				     "%s", _("Unable to get schema name"));
			return NULL;
		}

		snode = gda_tree_manager_create_node (manager, node, g_value_get_string (cvalue));
		gda_tree_node_set_node_attribute (snode, "schema", cvalue, NULL);
		list = g_slist_prepend (list, snode);
	}
	if (iter)
		g_object_unref (iter);
	g_object_unref (model);

	return list;
}
