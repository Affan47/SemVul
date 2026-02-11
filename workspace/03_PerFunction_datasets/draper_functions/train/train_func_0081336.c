create_combobox_list_store(char *list)
{
	GtkListStore	*list_store;
	GtkTreeIter	iter;
	int		i=0;
	char		**array;

	list_store = gtk_list_store_new (N_COLUMNS,
				   G_TYPE_STRING,
				   G_TYPE_INT,
				   G_TYPE_BOOLEAN);

	array = g_strsplit(list,"|",-1);

	while(array[i])
	{


		gtk_list_store_append (list_store, &iter);
		gtk_list_store_set (list_store, &iter,
				  COLUMN_STRING, array[i],
				  COLUMN_INT, i,
				  COLUMN_BOOLEAN,  FALSE,
				  -1);

		i++;
	}

	g_strfreev(array);
	return list_store;
}
