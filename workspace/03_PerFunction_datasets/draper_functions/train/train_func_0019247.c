_update_node_features(char *node_names, char *features)
{
	bitstr_t *node_bitmap = NULL, *tmp_bitmap;
	ListIterator config_iterator;
	struct config_record *config_ptr, *new_config_ptr;
	struct config_record *first_new = NULL;
	int rc, config_cnt, tmp_cnt;

	rc = node_name2bitmap(node_names, false, &node_bitmap);
	if (rc) {
		info("_update_node_features: invalid node_name");
		return rc;
	}


	config_iterator = list_iterator_create(config_list);
	while ((config_ptr = (struct config_record *)
			list_next(config_iterator))) {
		if (config_ptr == first_new)
			break;

		tmp_bitmap = bit_copy(node_bitmap);
		bit_and(tmp_bitmap, config_ptr->node_bitmap);
		config_cnt = bit_set_count(config_ptr->node_bitmap);
		tmp_cnt = bit_set_count(tmp_bitmap);
		if (tmp_cnt == 0) {

		} else if (tmp_cnt == config_cnt) {

			xfree(config_ptr->feature);
			if (features && features[0])
				config_ptr->feature = xstrdup(features);
			build_config_feature_list(config_ptr);
		} else {

			new_config_ptr = _dup_config(config_ptr);
			if (first_new == NULL);
				first_new = new_config_ptr;
			xfree(new_config_ptr->feature);
			if (features && features[0])
				new_config_ptr->feature = xstrdup(features);
			new_config_ptr->node_bitmap = bit_copy(tmp_bitmap);
			new_config_ptr->nodes = bitmap2node_name(tmp_bitmap);

			build_config_feature_list(new_config_ptr);
			_update_config_ptr(tmp_bitmap, new_config_ptr);


			bit_not(tmp_bitmap);
			bit_and(config_ptr->node_bitmap, tmp_bitmap);
			xfree(config_ptr->nodes);
			config_ptr->nodes = bitmap2node_name(config_ptr->
							     node_bitmap);
		}
		FREE_NULL_BITMAP(tmp_bitmap);
	}
	list_iterator_destroy(config_iterator);
	FREE_NULL_BITMAP(node_bitmap);

	info("_update_node_features: nodes %s features set to: %s",
		node_names, features);
	return SLURM_SUCCESS;
}
