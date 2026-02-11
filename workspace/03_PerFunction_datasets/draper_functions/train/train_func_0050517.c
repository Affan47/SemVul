da_tag_append(Tag *item)
{
Tag *existitem;
guint32 *new_key;

	DB( g_print("da_tag_append\n") );

	if( item->name != NULL )
	{


		existitem = da_tag_get_by_name( item->name );
		if( existitem == NULL )
		{
			new_key = g_new0(guint32, 1);
			*new_key = da_tag_get_max_key() + 1;
			item->key = *new_key;

			DB( g_print(" -> append id: %d\n", *new_key) );

			g_hash_table_insert(GLOBALS->h_tag, new_key, item);
			return TRUE;
		}
	}

	DB( g_print(" -> %s already exist: %d\n", item->name, item->key) );

	return FALSE;
}
