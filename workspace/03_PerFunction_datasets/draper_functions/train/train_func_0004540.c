verify_conn_type(const char *arg, uint16_t *conn_type)
{
	bool got_bgp = 0;
	int inx = 0;
	int highest_dims = 1;
	char *arg_tmp = xstrdup(arg), *tok, *save_ptr = NULL;

	if (working_cluster_rec) {
		if (working_cluster_rec->flags & CLUSTER_FLAG_BGP)
			got_bgp = 1;
		else if (working_cluster_rec->flags & CLUSTER_FLAG_BGQ)
			highest_dims = 4;
	} else {
#ifdef HAVE_BGP
		got_bgp = 1;
# elif defined HAVE_BGQ
		highest_dims = 4;
#endif
	}

	tok = strtok_r(arg_tmp, ",", &save_ptr);
	while (tok) {
		if (inx >= highest_dims) {
			error("too many conn-type arguments: %s", arg);
			break;
		}
		conn_type[inx++] = _get_conn_type(tok, got_bgp);
		tok = strtok_r(NULL, ",", &save_ptr);
	}
	if (inx == 0)
		error("invalid conn-type argument '%s' ignored.", arg);


	for ( ; inx < HIGHEST_DIMENSIONS; inx++) {
		conn_type[inx] = (uint16_t)NO_VAL;
	}

	xfree(arg_tmp);
}
