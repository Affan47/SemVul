gnet_host_vec_free(gnet_host_vec_t **vec_ptr)
{
	g_assert(vec_ptr != NULL);

	if (*vec_ptr) {
		gnet_host_vec_t *vec = *vec_ptr;

		WFREE_ARRAY_NULL(vec->hvec_v4, vec->n_ipv4);
		WFREE_ARRAY_NULL(vec->hvec_v6, vec->n_ipv6);
		WFREE(vec);
		*vec_ptr = NULL;
	}
}
