gda_server_operation_is_valid (GdaServerOperation *op, const gchar *xml_file, GError **error)
{
	gboolean valid = TRUE;
	GSList *list;

	g_return_val_if_fail (GDA_IS_SERVER_OPERATION (op), FALSE);
	g_return_val_if_fail (op->priv, FALSE);

	if (!xml_file) {

		for (list = op->priv->allnodes; list; list = list->next) {
			Node *node;

			node = NODE (list->data);
			if (node->status == GDA_SERVER_OPERATION_STATUS_REQUIRED) {
				if (node->type == GDA_SERVER_OPERATION_NODE_PARAM) {
					const GValue *value;
					gchar *path;

					path = node_get_complete_path (op, node);
					value = gda_server_operation_get_value_at (op, path);
					if (!value) {
						valid = FALSE;
						g_set_error (error,
							     GDA_SERVER_OPERATION_ERROR,
							     GDA_SERVER_OPERATION_INCORRECT_VALUE_ERROR,
							     _("Missing required value for '%s'"), path);
						break;
					}
					g_free (path);
				}
				else if (node->type == GDA_SERVER_OPERATION_NODE_PARAMLIST) {
					valid = gda_set_is_valid (node->d.plist, error);
					if (!valid)
						break;
				}
			}
		}
	}
	else {

		xmlNodePtr save;

		save = gda_server_operation_save_data_to_xml (op, error);
		if (save) {
			GdaServerOperation *op2;
			op2 = gda_server_operation_new (op->priv->op_type, xml_file);
			if (gda_server_operation_load_data_from_xml (op2, save, error))
				valid = gda_server_operation_is_valid (op2, NULL, error);
			else
				valid = FALSE;
			xmlFreeNode (save);
			g_object_unref (op2);
		}
		else
			valid = FALSE;
	}

	return valid;
}
