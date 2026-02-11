apol_validatetrans_get_by_query(const apol_policy_t * p, apol_validatetrans_query_t * vt, apol_vector_t ** v)
{
	qpol_iterator_t *iter = NULL;
	int retval = -1;
	*v = NULL;
	if (qpol_policy_get_validatetrans_iter(p->p, &iter) < 0) {
		return -1;
	}
	if ((*v = apol_vector_create(NULL)) == NULL) {
		ERR(p, "%s", strerror(errno));
		goto cleanup;
	}
	for (; !qpol_iterator_end(iter); qpol_iterator_next(iter)) {
		qpol_validatetrans_t *validatetrans;
		if (qpol_iterator_get_item(iter, (void **)&validatetrans) < 0) {
			goto cleanup;
		}
		if (vt != NULL) {
			const qpol_class_t *class_datum;
			const char *class_name;
			int compval;
			if (qpol_validatetrans_get_class(p->p, validatetrans, &class_datum) < 0 ||
			    qpol_class_get_name(p->p, class_datum, &class_name) < 0) {
				goto cleanup;
			}
			compval = apol_compare(p, class_name, vt->class_name, vt->flags, &(vt->regex));
			if (compval < 0) {
				goto cleanup;
			} else if (compval == 0) {
				free(validatetrans);
				continue;
			}
		}
		if (apol_vector_append(*v, validatetrans)) {
			ERR(p, "%s", strerror(ENOMEM));
			goto cleanup;
		}
	}

	retval = 0;
      cleanup:
	if (retval != 0) {
		apol_vector_destroy(v);
	}
	qpol_iterator_destroy(&iter);
	return retval;
}
