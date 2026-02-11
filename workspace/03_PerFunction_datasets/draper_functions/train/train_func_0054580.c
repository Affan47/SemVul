_update_node_gres(char *node_names, char *gres)
{
	bitstr_t *node_bitmap = NULL, *tmp_bitmap;
	ListIterator config_iterator;
	struct config_record *config_ptr, *new_config_ptr;
	struct config_record *first_new = NULL;
	struct node_record *node_ptr;
	int rc, config_cnt, tmp_cnt;
	int i, i_first, i_last;

	rc = node_name2bitmap(node_names, false, &node_bitmap);
	if (rc) {
		info("_update_node_gres: invalid node_name");
		return rc;
	}


	config_iterator = list_iterator_create(config_list);
	if (config_iterator == NULL)
		fatal("list_iterator_create malloc failure");
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

			xfree(config_ptr->gres);
			if (gres && gres[0])
				config_ptr->gres = xstrdup(gres);
		} else {

			new_config_ptr = _dup_config(config_ptr);
			if (first_new == NULL);
				first_new = new_config_ptr;
			xfree(new_config_ptr->gres);
			if (gres && gres[0])
				new_config_ptr->gres = xstrdup(gres);
			new_config_ptr->node_bitmap = bit_copy(tmp_bitmap);
			new_config_ptr->nodes = bitmap2node_name(tmp_bitmap);

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

	i_first = bit_ffs(node_bitmap);
	i_last  = bit_fls(node_bitmap);
	for (i=i_first; i<=i_last; i++) {
		node_ptr = node_record_table_ptr + i;
		(void) gres_plugin_node_reconfig(node_ptr->name,
						 node_ptr->config_ptr->gres,
						 &node_ptr->gres,
						 &node_ptr->gres_list,
						 slurmctld_conf.fast_schedule);
		gres_plugin_node_state_log(node_ptr->gres_list, node_ptr->name);
	}
	FREE_NULL_BITMAP(node_bitmap);

	info("_update_node_gres: nodes %s gres set to: %s", node_names, gres);
	return SLURM_SUCCESS;
}
