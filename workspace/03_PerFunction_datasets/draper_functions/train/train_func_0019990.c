init_content_list_store(gboolean populate)
{
	GtkListStore	*store;

	store = gtk_list_store_new(CONTENT_COLUMN_COUNT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
	if(store != NULL && populate)
	{
		GtkTreeIter	iter;
		guint		i;

		for(i = 0; i < DPC_NUM_TYPES; i++)
		{
			if(i == DPC_BLOCKS || i == DPC_BLOCKSIZE)
				continue;
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter,
						CONTENT_COLUMN_TITLE, dpf_get_content_title((DPContent) i),
						CONTENT_COLUMN_DESCRIPTION, dpf_get_content_name((DPContent) i),
						CONTENT_COLUMN_CONTENT, i,
						-1);
		}
	}
	return store;
}
