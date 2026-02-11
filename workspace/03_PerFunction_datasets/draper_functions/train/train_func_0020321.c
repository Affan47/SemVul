gcr_collection_model_real_iter_next (GtkTreeModel *model,
                                     GtkTreeIter *iter)
{
	GcrCollectionModel *self = GCR_COLLECTION_MODEL (model);
	GSequenceIter *seq = sequence_iter_for_tree (self, iter);
	g_return_val_if_fail (seq != NULL, FALSE);
	return sequence_iter_to_tree (self, g_sequence_iter_next (seq), iter);
}
