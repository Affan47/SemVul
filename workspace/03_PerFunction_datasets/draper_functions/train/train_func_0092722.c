eprop_model_data_generate_store (GladeEditorProperty *eprop)
{
	GtkListStore   *store = NULL;
	GladeModelData *iter_data, *row_data;
	GNode          *data_tree = NULL, *iter_node, *row_node;
	GArray         *gtypes = g_array_new (FALSE, TRUE, sizeof (GType));
	GtkTreeIter     iter;
	gint            column_num, row_num;
	GType           index_type = G_TYPE_INT, string_type = G_TYPE_STRING, pointer_type = G_TYPE_POINTER;

	glade_property_get (eprop->property, &data_tree);

	if (!data_tree || !data_tree->children || !data_tree->children->children)
		return NULL;


	g_array_append_val (gtypes, index_type);
	for (iter_node = data_tree->children->children; iter_node; iter_node = iter_node->next)
	{
		iter_data = iter_node->data;
		if (G_VALUE_TYPE (&iter_data->value) == 0)
			g_array_append_val (gtypes, pointer_type);
		else if (G_VALUE_TYPE (&iter_data->value) == GDK_TYPE_PIXBUF)
			g_array_append_val (gtypes, string_type);
		else
			g_array_append_val (gtypes, G_VALUE_TYPE (&iter_data->value));
	}
	store = gtk_list_store_newv (gtypes->len, (GType *)gtypes->data);
	g_array_free (gtypes, TRUE);


	for (row_num = 0, row_node = data_tree->children; row_node;
	     row_num++, row_node = row_node->next)
	{
		row_data = row_node->data;

		gtk_list_store_append (store, &iter);
		gtk_list_store_set (store, &iter, COLUMN_ROW, row_num, -1);

		for (column_num = NUM_COLUMNS, iter_node = row_node->children; iter_node;
		     column_num++, iter_node = iter_node->next)
		{
			iter_data = iter_node->data;

			if (G_VALUE_TYPE (&iter_data->value) == 0)
				continue;


			if (G_VALUE_TYPE (&iter_data->value) == GDK_TYPE_PIXBUF)
			{
				GObject *object = g_value_get_object (&iter_data->value);
				gchar *filename = NULL;
				if (object)
					filename = g_object_get_data (object, "GladeFileName");

				gtk_list_store_set (store, &iter,
						    column_num, filename,
						    -1);
			}
			else
				gtk_list_store_set_value (store, &iter, column_num, &iter_data->value);
		}
	}
	return store;
}
