create_default_portset(isc_mem_t *mctx, isc_portset_t **portsetp) {
	isc_result_t result;

	result = isc_portset_create(mctx, portsetp);
	if (result != ISC_R_SUCCESS)
		return (result);
	isc_portset_addrange(*portsetp, 1024, 65535);

	return (ISC_R_SUCCESS);
}
