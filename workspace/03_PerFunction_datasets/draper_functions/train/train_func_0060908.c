type_get_attrib_names(const poldiff_t * diff, const apol_policy_t * p, uint32_t type)
{
	qpol_iterator_t *attrib_iter = NULL;
	const char *attrib;
	char *new_attrib;
	const apol_vector_t *v = NULL;
	apol_vector_t *ret = NULL;
	qpol_type_t *qt = NULL;
	qpol_policy_t *q = apol_policy_get_qpol(p);
	int retval = -1;
	size_t i;

	if ((ret = apol_vector_create(free)) == NULL) {
		ERR(diff, "%s", strerror(errno));
		return NULL;
	}


	v = type_map_lookup_reverse(diff, type, (diff->orig_pol == p ? POLDIFF_POLICY_ORIG : POLDIFF_POLICY_MOD));
	if (apol_vector_get_size(v) == 0) {
		assert(false);
		return NULL;
	}

	for (i = 0; i < apol_vector_get_size(v); i++) {
		qt = apol_vector_get_element(v, i);
		if (qt == NULL) {
			assert(false);
			return NULL;
		}
		qpol_type_get_attr_iter(q, qt, &attrib_iter);
		for (; !qpol_iterator_end(attrib_iter); qpol_iterator_next(attrib_iter)) {

			if (qpol_iterator_get_item(attrib_iter, (void **)&qt) < 0) {
				goto cleanup;
			}
			qpol_type_get_name(q, qt, &attrib);
			if ((new_attrib = strdup(attrib)) == NULL || apol_vector_append(ret, new_attrib) < 0) {
				ERR(diff, "%s", strerror(errno));
				goto cleanup;
			}
		}
	}
	apol_vector_sort_uniquify(ret, &apol_str_strcmp, NULL);
	retval = 0;
      cleanup:
	qpol_iterator_destroy(&attrib_iter);
	if (retval < 0) {
		apol_vector_destroy(&ret);
		return NULL;
	}
	return ret;
}
