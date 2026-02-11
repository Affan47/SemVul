on_collection_added (GcrCollection *collection,
                     GObject *object,
                     gpointer user_data)
{
	GcrCollectionModel *self = GCR_COLLECTION_MODEL (user_data);
	GSequence *sequence;
	GSequenceIter *parent;
	GcrCollectionRow *row;

	if (collection == self->pv->collection) {
		sequence = self->pv->root_sequence;
		parent = NULL;
	} else {
		parent = g_hash_table_lookup (self->pv->object_to_seq, G_OBJECT (collection));
		row = g_sequence_get (parent);
		g_assert (row->children);
		sequence = row->children;
	}

	add_object_to_sequence (self, sequence, parent, object, TRUE);
}
