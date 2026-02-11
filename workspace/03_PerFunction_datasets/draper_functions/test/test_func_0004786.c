apol_types_relation_transflow(const apol_policy_t * p,
					 const qpol_type_t * typeA,
					 const qpol_type_t * typeB,
					 unsigned int do_transAB, unsigned int do_transBA, apol_types_relation_result_t * r)
{
	const char *nameA, *nameB;
	apol_infoflow_analysis_t *ia = NULL;
	apol_vector_t *v = NULL;
	apol_infoflow_graph_t *g = NULL;
	int retval = -1;

	if (qpol_type_get_name(p->p, typeA, &nameA) < 0 || qpol_type_get_name(p->p, typeB, &nameB) < 0) {
		goto cleanup;
	}
	if ((ia = apol_infoflow_analysis_create()) == NULL) {
		ERR(p, "%s", strerror(ENOMEM));
		goto cleanup;
	}
	if (apol_infoflow_analysis_set_mode(p, ia, APOL_INFOFLOW_MODE_TRANS) < 0 ||
	    apol_infoflow_analysis_set_dir(p, ia, APOL_INFOFLOW_OUT) < 0) {
		goto cleanup;
	}
	if (do_transAB) {
		if (apol_infoflow_analysis_set_type(p, ia, nameA) < 0 || apol_infoflow_analysis_do(p, ia, &v, &g) < 0) {
			goto cleanup;
		}
		if ((r->transAB = apol_vector_create(infoflow_result_free)) == NULL) {
			ERR(p, "%s", strerror(errno));
			goto cleanup;
		}
		if (apol_types_relation_clone_infoflow(p, v, nameB, r->transAB) < 0) {
			goto cleanup;
		}
	}
	if (do_transBA) {
		apol_vector_destroy(&v);
		if ((do_transAB &&
		     apol_infoflow_analysis_do_more(p, g, nameB, &v) < 0) ||
		    (!do_transAB &&
		     (apol_infoflow_analysis_set_type(p, ia, nameB) < 0 || apol_infoflow_analysis_do(p, ia, &v, &g) < 0))) {
			goto cleanup;
		}
		if ((r->transBA = apol_vector_create(infoflow_result_free)) == NULL) {
			ERR(p, "%s", strerror(errno));
			goto cleanup;
		}
		if (apol_types_relation_clone_infoflow(p, v, nameA, r->transBA) < 0) {
			goto cleanup;
		}
	}
	retval = 0;
      cleanup:
	apol_vector_destroy(&v);
	apol_infoflow_analysis_destroy(&ia);
	apol_infoflow_graph_destroy(&g);
	return retval;
}
