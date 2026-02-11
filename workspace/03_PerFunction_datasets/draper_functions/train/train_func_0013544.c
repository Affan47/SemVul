_valid_node_feature(char *feature)
{
	int rc = ESLURM_INVALID_FEATURE;
	struct features_record *feature_ptr;
	ListIterator feature_iter;


	feature_iter = list_iterator_create(feature_list);
	while ((feature_ptr = (struct features_record *)
			list_next(feature_iter))) {
		if (strcmp(feature_ptr->name, feature))
			continue;
		rc = SLURM_SUCCESS;
		break;
	}
	list_iterator_destroy(feature_iter);

	return rc;
}
