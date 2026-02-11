apol_infoflow_graph_create_avrule(const apol_policy_t * p, apol_infoflow_graph_t * g, const qpol_avrule_t * rule,
					     apol_bst_t * types, int max_len)
{
	const qpol_class_t *obj_class;
	qpol_iterator_t *perm_iter = NULL;
	const char *obj_class_name;
	char *perm_name;
	int found_read = 0, found_write = 0, perm_error = 0;
	int read_len = INT_MAX, write_len = INT_MAX;
	int retval = -1;
	if (qpol_avrule_get_object_class(p->p, rule, &obj_class) < 0 ||
	    qpol_class_get_name(p->p, obj_class, &obj_class_name) < 0 || qpol_avrule_get_perm_iter(p->p, rule, &perm_iter) < 0) {
		goto cleanup;
	}


	for (; !qpol_iterator_end(perm_iter); qpol_iterator_next(perm_iter)) {
		int perm_map, perm_weight, len;

		if (qpol_iterator_get_item(perm_iter, (void **)&perm_name) < 0) {
			goto cleanup;
		}
		if (apol_policy_get_permmap(p, obj_class_name, perm_name, &perm_map, &perm_weight) < 0) {
			goto cleanup;
		}
		free(perm_name);
		if (perm_map == APOL_PERMMAP_UNMAPPED) {
			perm_error = 1;
			continue;
		}
		len = APOL_PERMMAP_MAX_WEIGHT - perm_weight + 1;
		if (len < APOL_PERMMAP_MIN_WEIGHT) {
			len = APOL_PERMMAP_MIN_WEIGHT;
		} else if (len > APOL_PERMMAP_MAX_WEIGHT) {
			len = APOL_PERMMAP_MAX_WEIGHT;
		}
		if (perm_map & APOL_PERMMAP_READ) {
			if (len < read_len && len <= max_len) {
				found_read = 1;
				read_len = len;
			}
		}
		if (perm_map & APOL_PERMMAP_WRITE) {
			if (len < write_len && len <= max_len) {
				found_write = 1;
				write_len = len;
			}
		}
	}


	if ((found_read || found_write) &&
	    apol_infoflow_graph_connect_nodes(p, g, rule, types, found_read, read_len, found_write, write_len) < 0) {
		goto cleanup;
	}
	if (perm_error) {
		WARN(p, "%s", "Not all of the permissions found had associated permission maps.");
	}

	retval = 0;
      cleanup:
	qpol_iterator_destroy(&perm_iter);
	return retval;
}
