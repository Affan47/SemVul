gres_plugin_init_node_config(char *node_name, char *orig_config,
					List *gres_list)
{
	int i, rc;
	ListIterator gres_iter;
	gres_state_t *gres_ptr;

	rc = gres_plugin_init();

	slurm_mutex_lock(&gres_context_lock);
	if ((gres_context_cnt > 0) && (*gres_list == NULL)) {
		*gres_list = list_create(_gres_node_list_delete);
		if (*gres_list == NULL)
			fatal("list_create malloc failure");
	}
	for (i=0; ((i < gres_context_cnt) && (rc == SLURM_SUCCESS)); i++) {

		gres_iter = list_iterator_create(*gres_list);
		while ((gres_ptr = (gres_state_t *) list_next(gres_iter))) {
			if (gres_ptr->plugin_id == gres_context[i].plugin_id)
				break;
		}
		list_iterator_destroy(gres_iter);
		if (gres_ptr == NULL) {
			gres_ptr = xmalloc(sizeof(gres_state_t));
			gres_ptr->plugin_id = gres_context[i].plugin_id;
			list_append(*gres_list, gres_ptr);
		}

		rc = _node_config_init(node_name, orig_config,
				       &gres_context[i], gres_ptr);
	}
	slurm_mutex_unlock(&gres_context_lock);

	return rc;
}
