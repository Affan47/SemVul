relabel_analysis_matchup(const apol_policy_t * p,
				    apol_relabel_analysis_t * r,
				    apol_vector_t * av, apol_vector_t * bv, const apol_vector_t * subjects_v, apol_vector_t * v)
{
	const qpol_avrule_t *a_avrule, *b_avrule;
	const qpol_type_t *a_source, *a_target, *b_source, *b_target, *start_type;
	const qpol_class_t *a_class, *b_class;
	apol_vector_t *start_v = NULL;
	size_t i, j;
	int compval, retval = -1;

	if (apol_query_get_type(p, r->type, &start_type) < 0) {
		goto cleanup;
	}
	for (i = 0; i < apol_vector_get_size(av); i++) {
		a_avrule = apol_vector_get_element(av, i);
		if (qpol_avrule_get_source_type(p->p, a_avrule, &a_source) < 0 ||
		    qpol_avrule_get_target_type(p->p, a_avrule, &a_target) < 0 ||
		    qpol_avrule_get_object_class(p->p, a_avrule, &a_class) < 0) {
			goto cleanup;
		}
		compval = relabel_analysis_compare_type_to_vector(p, subjects_v, a_source);
		if (compval < 0) {
			goto cleanup;
		} else if (compval == 0) {
			continue;
		}
		if ((start_v = apol_query_expand_type(p, a_source)) == NULL) {
			goto cleanup;
		}


		for (j = 0; j < apol_vector_get_size(bv); j++) {
			b_avrule = apol_vector_get_element(bv, j);
			if (qpol_avrule_get_source_type(p->p, b_avrule, &b_source) < 0 ||
			    qpol_avrule_get_target_type(p->p, b_avrule, &b_target) < 0 ||
			    qpol_avrule_get_object_class(p->p, b_avrule, &b_class) < 0) {
				goto cleanup;
			}
			if (relabel_analysis_compare_type_to_vector(p, start_v, b_source) != 1 ||
			    b_target == start_type || a_class != b_class) {
				continue;
			}
			if (append_avrules_to_object_vector(p, r, a_avrule, b_avrule, v) < 0) {
				goto cleanup;
			}
		}
		apol_vector_destroy(&start_v);
	}

	retval = 0;
      cleanup:
	apol_vector_destroy(&start_v);
	return retval;
}
