data_book_view_finalize (GObject *object)
{
	EDataBookViewPrivate *priv;

	priv = E_DATA_BOOK_VIEW_GET_PRIVATE (object);

	g_free (priv->object_path);

	reset_array (priv->adds);
	reset_array (priv->changes);
	reset_array (priv->removes);
	g_array_free (priv->adds, TRUE);
	g_array_free (priv->changes, TRUE);
	g_array_free (priv->removes, TRUE);

	if (priv->fields_of_interest)
		g_hash_table_destroy (priv->fields_of_interest);

	g_mutex_clear (&priv->pending_mutex);

	g_hash_table_destroy (priv->ids);


	G_OBJECT_CLASS (e_data_book_view_parent_class)->finalize (object);
}
