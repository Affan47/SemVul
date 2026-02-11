store_closure_free (gpointer data)
{
	StoreClosure *store = data;
	if (store->cancellable)
		g_object_unref (store->cancellable);
	g_free (store->collection_path);
	secret_value_unref (store->value);
	g_hash_table_unref (store->properties);
	g_slice_free (StoreClosure, store);
}
