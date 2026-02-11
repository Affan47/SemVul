dig_clean(dig_params_t *params)
{
	node_t *n = NULL, *nxt = NULL;

	if (params == NULL) {
		DBG_NULL;
		return;
	}


	WALK_LIST_DELSAFE(n, nxt, params->queries) {
		query_free((query_t *)n);
	}


	query_free((query_t *)params->config);


	memset(params, 0, sizeof(*params));
}
