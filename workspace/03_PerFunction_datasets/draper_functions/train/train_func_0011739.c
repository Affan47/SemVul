debug_tree_find_name (const GtkTreeModel *model, GtkTreeIter *iter, const gchar *name)
{
	size_t len = 0;
	GtkTreeIter parent_iter;
	GtkTreeIter* parent = NULL;

	for (;;)
	{
		const gchar *ptr;


		ptr = strchr(name + len + 1, '.');
		if (ptr != NULL)
		{

			gboolean search;

			len = ptr - name;
			for (search = gtk_tree_model_iter_children (GTK_TREE_MODEL (model), iter, parent);
				search != FALSE;
	    		search = gtk_tree_model_iter_next (GTK_TREE_MODEL (model), iter))
			{
				DmaVariableData *iData;
        		gtk_tree_model_get (GTK_TREE_MODEL (model), iter, DTREE_ENTRY_COLUMN, &iData, -1);

				if ((iData != NULL) && (iData->name != NULL) && (name[len] == '.') && (strncmp (name, iData->name, len) == 0))
				{
					break;
				}
			}

			if (search == TRUE)
			{
				parent_iter = *iter;
				parent = &parent_iter;
				continue;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{

			gboolean search;

			for (search = gtk_tree_model_iter_children (GTK_TREE_MODEL (model), iter, parent);
				search != FALSE;
				search = gtk_tree_model_iter_next (GTK_TREE_MODEL (model), iter))
			{
				DmaVariableData *iData;
				gtk_tree_model_get (GTK_TREE_MODEL (model), iter, DTREE_ENTRY_COLUMN, &iData, -1);

				if ((iData != NULL) && (iData->name != NULL) && (strcmp (name, iData->name) == 0))
				{
					return TRUE;
				}
			}

			return FALSE;
		}
	}
}
