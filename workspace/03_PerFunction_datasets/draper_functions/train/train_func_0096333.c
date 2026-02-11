remove_object_from_module (GkmXdgModule *self, GkmObject *object,
                           const gchar *filename, GkmTransaction *transaction)
{
	gkm_object_expose (object, FALSE);

	if (transaction != NULL)
		gkm_transaction_add (transaction, self, complete_remove_object, g_object_ref (object));

	g_assert (g_hash_table_lookup (self->objects_by_path, filename) == object);
	g_hash_table_remove (self->objects_by_path, filename);
}
