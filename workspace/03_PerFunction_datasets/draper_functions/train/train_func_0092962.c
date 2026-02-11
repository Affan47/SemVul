e_destination_store_remove_destination_nth (EDestinationStore *destination_store,
                                            gint n)
{
	EDestination *destination;
	GPtrArray *array;

	g_return_if_fail (n >= 0);

	array = destination_store->priv->destinations;
	destination = g_ptr_array_index (array, n);
	stop_destination (destination_store, destination);
	g_object_unref (destination);

	g_ptr_array_remove_index (array, n);
	row_deleted (destination_store, n);
}
