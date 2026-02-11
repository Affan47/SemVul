debug_tree_add_children (GtkTreeModel *model, DmaDebuggerQueue *debugger, GtkTreeIter* parent, guint from, const GList *children)
{
	GList *child;
	GtkTreeIter iter;
	gboolean valid;

	valid = gtk_tree_model_iter_nth_child (model, &iter, parent, from);


	for (child = g_list_first ((GList *)children); child != NULL; child = g_list_next (child))
	{
		IAnjutaDebuggerVariableObject *var = (IAnjutaDebuggerVariableObject *)child->data;
		DmaVariableData *data;

		if (!valid)
		{

			gtk_tree_store_append(GTK_TREE_STORE(model), &iter, parent);

			gtk_tree_store_set(GTK_TREE_STORE(model), &iter,
				TYPE_COLUMN, var->type == NULL ? UNKNOWN_TYPE : var->type,
				VALUE_COLUMN, var->value == NULL ? UNKNOWN_VALUE : var->value,
				VARIABLE_COLUMN, var->expression,
				ROOT_COLUMN, FALSE,
				DTREE_ENTRY_COLUMN, NULL,-1);
			data = NULL;
		}
		else
		{

			if (var->type != NULL)
				gtk_tree_store_set(GTK_TREE_STORE(model), &iter, TYPE_COLUMN, var->type, -1);
			if (var->value != NULL)
				gtk_tree_store_set(GTK_TREE_STORE(model), &iter, VALUE_COLUMN, var->value, -1);
			if (var->expression != NULL)
				gtk_tree_store_set(GTK_TREE_STORE(model), &iter, VARIABLE_COLUMN, var->expression, -1);
			gtk_tree_model_get(model, &iter, DTREE_ENTRY_COLUMN, &data, -1);

			if (var->name == NULL)
			{

				if (data != NULL)
				{
					dma_variable_data_free (data);
					gtk_tree_store_set(GTK_TREE_STORE (model), &iter, DTREE_ENTRY_COLUMN, NULL, -1);
					data = NULL;
				}
			}
		}

		if ((var->name != NULL) && (data == NULL))
		{

			data = dma_variable_data_new(var->name, TRUE);
			gtk_tree_store_set(GTK_TREE_STORE(model), &iter, DTREE_ENTRY_COLUMN, data, -1);
		}


		debug_tree_remove_children (model, debugger, &iter, NULL);
		if ((var->children != 0) || var->has_more || (var->name == NULL))
		{

			debug_tree_model_add_dummy_children (model, &iter);
		}

		valid = gtk_tree_model_iter_next (model, &iter);
	}


	if (valid) debug_tree_remove_children (model, debugger, parent, &iter);
}
