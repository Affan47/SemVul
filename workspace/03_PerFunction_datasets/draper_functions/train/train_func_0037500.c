cleanup_lease6(ia_hash_t *ia_table,
	       struct ipv6_pool *pool,
	       struct iasubopt *lease,
	       struct ia_xx *ia) {

	struct iasubopt *test_iasubopt, *tmp_iasubopt;
	struct ia_xx *old_ia;
	isc_result_t status = ISC_R_SUCCESS;

	test_iasubopt = NULL;
	old_ia = NULL;


	if (iasubopt_hash_lookup(&test_iasubopt, pool->leases,
				 &lease->addr, sizeof(lease->addr),
				 MDL) == 0) {
		return (ISC_R_SUCCESS);
	}

	if (test_iasubopt->ia == NULL) {

		iasubopt_dereference(&test_iasubopt, MDL);
		return (status);
	}

	ia_reference(&old_ia, test_iasubopt->ia, MDL);

	if ((old_ia->iaid_duid.len == ia->iaid_duid.len) &&
	    (memcmp((unsigned char *)ia->iaid_duid.data,
		    (unsigned char *)old_ia->iaid_duid.data,
		    ia->iaid_duid.len) == 0)) {

		if ((lease->state == FTS_ACTIVE) ||
		    (lease->state == FTS_ABANDONED)) {

			goto cleanup;
		}
	} else {

		if ((lease->state != FTS_ACTIVE) &&
		    (lease->state != FTS_ABANDONED)) {

			goto cleanup;
		}


		status = ISC_R_FAILURE;
	}


	isc_heap_delete(pool->active_timeouts, test_iasubopt->heap_index);
	pool->num_active--;

	iasubopt_hash_delete(pool->leases, &test_iasubopt->addr,
			     sizeof(test_iasubopt->addr), MDL);
	ia_remove_iasubopt(old_ia, test_iasubopt, MDL);
	if (old_ia->num_iasubopt <= 0) {
		ia_hash_delete(ia_table,
			       (unsigned char *)old_ia->iaid_duid.data,
			       old_ia->iaid_duid.len, MDL);
	}


	tmp_iasubopt = test_iasubopt;
	iasubopt_dereference(&tmp_iasubopt, MDL);

      cleanup:
	ia_dereference(&old_ia, MDL);


	iasubopt_dereference(&test_iasubopt, MDL);

	return (status);
}
