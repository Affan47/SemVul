gcr_collection_model_set_collection (GcrCollectionModel *self,
                                     GcrCollection *collection)
{
	GcrCollection *previous;
	GHashTable *exclude;
	GList *children = NULL;
	GList *l;

	g_return_if_fail (GCR_IS_COLLECTION_MODEL (self));
	g_return_if_fail (collection == NULL || GCR_IS_COLLECTION (collection));

	if (collection == self->pv->collection)
		return;

	if (collection)
		g_object_ref (collection);
	previous = self->pv->collection;
	self->pv->collection = collection;

	if (collection)
		children = gcr_collection_get_objects (collection);

	if (previous) {
		exclude = g_hash_table_new (g_direct_hash, g_direct_equal);
		for (l = children; l != NULL; l = g_list_next (l))
			g_hash_table_insert (exclude, l->data, l->data);

		remove_children_from_sequence (self, self->pv->root_sequence,
		                               previous, exclude, TRUE);

		g_hash_table_destroy (exclude);
		g_object_unref (previous);
	}

	if (collection) {
		add_children_to_sequence (self, self->pv->root_sequence,
		                          NULL, collection, children,
		                          self->pv->object_to_seq, TRUE);
		g_list_free (children);
	}

	g_object_notify (G_OBJECT (self), "collection");
}
