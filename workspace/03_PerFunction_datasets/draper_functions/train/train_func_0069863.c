table_add_terule(apol_policy_t * policy, apol_domain_trans_table_t * dta_table, const qpol_terule_t * rule)
{
	qpol_policy_t *qp = apol_policy_get_qpol(policy);
	const qpol_type_t *src;
	const qpol_type_t *tgt;
	const qpol_type_t *dflt;
	qpol_terule_get_source_type(qp, rule, &src);
	qpol_terule_get_target_type(qp, rule, &tgt);
	qpol_terule_get_default_type(qp, rule, &dflt);
	apol_vector_t *sources = apol_query_expand_type(policy, src);
	apol_vector_t *targets = apol_query_expand_type(policy, tgt);
	int error = 0;
	for (size_t i = 0; i < apol_vector_get_size(targets); i++) {
		ep_node_t *enode = NULL;
		ep_node_t dummy = { apol_vector_get_element(targets, i), NULL, NULL };
		if (apol_bst_get_element(dta_table->entrypoint_table, &dummy, NULL, (void **)&enode)) {
			ep_node_t *new_enode = NULL;
			if (!(new_enode = ep_node_create(dummy.type)) ||
			    apol_bst_insert(dta_table->entrypoint_table, (void *)new_enode, NULL)) {
				error = errno;
				ep_node_free(new_enode);
				goto err;
			}
			enode = new_enode;
		}
		for (size_t j = 0; j < apol_vector_get_size(sources); j++) {
			terule_node_t *new_node =
				terule_node_create((const qpol_type_t *)apol_vector_get_element(sources, j), dflt, rule);
			if (apol_bst_insert_and_get(enode->type_transition_tree, (void **)&new_node, NULL) < 0) {
				error = errno;
				free(new_node);
				goto err;
			}
		}
	}

	apol_vector_destroy(&sources);
	apol_vector_destroy(&targets);
	return 0;
      err:
	apol_vector_destroy(&sources);
	apol_vector_destroy(&targets);
	errno = error;
	return -1;
}
