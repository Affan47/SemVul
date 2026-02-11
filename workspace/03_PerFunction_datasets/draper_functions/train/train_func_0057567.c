find_connection (CEPageMaster *self, NMRemoteConnection *connection, GtkTreeIter *iter)
{
	CEPageMasterPrivate *priv = CE_PAGE_MASTER_GET_PRIVATE (self);

	if (!gtk_tree_model_get_iter_first (priv->connections_model, iter))
		return FALSE;

	do {
		NMRemoteConnection *candidate = NULL;

		gtk_tree_model_get (priv->connections_model, iter,
		                    COL_CONNECTION, &candidate,
		                    -1);
		if (candidate == connection)
			return TRUE;
	} while (gtk_tree_model_iter_next (priv->connections_model, iter));

	return FALSE;
}
