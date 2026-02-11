removeRow(char *key)
{
	gTreeRow *row;
	char *child;

	if (!key || !*key)  return false;

	row=(gTreeRow*)g_hash_table_lookup(datakey, (gconstpointer)key);
	if (!row) return false;


	while((child = row->child()))
		removeRow(child);


	g_hash_table_remove (datakey, (gconstpointer)key);
	gtk_tree_store_remove(store, row->dataiter);
	delete row;

	return true;
}
