verify_nsec3_chains(isc_mem_t *mctx) {
	isc_result_t result = ISC_R_SUCCESS;
	struct nsec3_chain_fixed *e, *f = NULL;
	struct nsec3_chain_fixed *first = NULL, *prev = NULL;

	while ((e = isc_heap_element(expected_chains, 1)) != NULL) {
		isc_heap_delete(expected_chains, 1);
		if (f == NULL)
			f = isc_heap_element(found_chains, 1);
		if (f != NULL) {
			isc_heap_delete(found_chains, 1);


			if (chain_equal(e, f)) {
				free_element(mctx, f);
				f = NULL;
			} else {
				if (result == ISC_R_SUCCESS)
					fprintf(stderr, EXPECTEDANDFOUND);
				result = ISC_R_FAILURE;


				while (f != NULL && !chain_compare(e, f)) {
					free_element(mctx, f);
					f = isc_heap_element(found_chains, 1);
					if (f != NULL)
						isc_heap_delete(found_chains, 1);
					if (f != NULL && chain_equal(e, f)) {
						free_element(mctx, f);
						f = NULL;
						break;
					}
				}
			}
		} else if (result == ISC_R_SUCCESS) {
			fprintf(stderr, EXPECTEDANDFOUND);
			result = ISC_R_FAILURE;
		}
		if (first == NULL || newchain(first, e)) {
			if (prev != NULL) {
				if (!checknext(prev, first))
					result = ISC_R_FAILURE;
				if (prev != first)
					free_element(mctx, prev);
			}
			if (first != NULL)
				free_element(mctx, first);
			prev = first = e;
			continue;
		}
		if (!checknext(prev, e))
			result = ISC_R_FAILURE;
		if (prev != first)
			free_element(mctx, prev);
		prev = e;
	}
	if (prev != NULL) {
		if (!checknext(prev, first))
			result = ISC_R_FAILURE;
		if (prev != first)
			free_element(mctx, prev);
	}
	if (first != NULL)
		free_element(mctx, first);
	do {
		if (f != NULL) {
			if (result == ISC_R_SUCCESS) {
				fprintf(stderr, EXPECTEDANDFOUND);
				result = ISC_R_FAILURE;
			}
			free_element(mctx, f);
		}
		f = isc_heap_element(found_chains, 1);
		if (f != NULL)
			isc_heap_delete(found_chains, 1);
	} while (f != NULL);

	return (result);
}
