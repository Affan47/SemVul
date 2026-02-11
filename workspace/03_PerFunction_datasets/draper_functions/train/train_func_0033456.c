gda_server_operation_get_node_type (GdaServerOperation *op, const gchar *path,
				    GdaServerOperationNodeStatus *status)
{
	GdaServerOperationNode *node_info;

	g_return_val_if_fail (GDA_IS_SERVER_OPERATION (op), GDA_SERVER_OPERATION_NODE_UNKNOWN);
	g_return_val_if_fail (op->priv, GDA_SERVER_OPERATION_NODE_UNKNOWN);

	node_info = gda_server_operation_get_node_info (op, path);
	if (node_info) {
		if (status)
			*status = node_info->status;
		return node_info->type;
	}
	return GDA_SERVER_OPERATION_NODE_UNKNOWN;
}
