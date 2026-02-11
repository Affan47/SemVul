_list_delete_feature (void *feature_entry)
{
	struct features_record *feature_ptr = (struct features_record *)
					     feature_entry;

	xassert(feature_ptr);
	xassert(feature_ptr->magic == FEATURE_MAGIC);
	xfree (feature_ptr->name);
	FREE_NULL_BITMAP (feature_ptr->node_bitmap);
	xfree (feature_ptr);
}
