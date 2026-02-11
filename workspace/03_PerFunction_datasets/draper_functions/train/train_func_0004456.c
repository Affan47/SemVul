glade_model_data_insert_column (GNode          *node,
				GType           type,
				const gchar    *column_name,
				gint            nth)
{
	GNode *row, *item;
	GladeModelData *data;

	g_return_if_fail (node != NULL);

	for (row = node->children; row; row = row->next)
	{
		g_return_if_fail (nth >= 0 && nth <= g_node_n_children (row));

		data = glade_model_data_new (type, column_name);
		item = g_node_new (data);
		g_node_insert (row, nth, item);
	}
}
