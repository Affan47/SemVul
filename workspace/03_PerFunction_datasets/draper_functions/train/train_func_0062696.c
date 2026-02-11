paraccess_list(int opt_concurrency, int opt_udp_only,
	char *opt_architecture, char *opt_domainname, int opt_port,
	int opt_plain_order, int opt_sort_by_loadavg,
	int opt_use_metadb, int nhosts, char **hosts,
	gfarm_error_t (*request_op)(struct gfarm_host_info *,
	    struct gfarm_paraccess *),
	void (*callback_op)(struct output *))
{
	gfarm_error_t e, e_save;
	struct gfarm_paraccess *pa;

	if (opt_plain_order)
		output_record = 0;
	else
		output_record = 1;

	output_callback = callback_op;

	e = gfarm_paraccess_alloc(opt_concurrency, !opt_udp_only, &pa);
	if (e != GFARM_ERR_NO_ERROR) {
		fprintf(stderr, "%s: %s\n",
		    program_name, gfarm_error_string(e));
		exit(1);
	}

	if (nhosts == 0) {
		e_save = list_all(opt_architecture, opt_domainname,
			request_op, pa);
	} else if (opt_use_metadb) {
		e_save = list(nhosts, hosts, request_op, pa);
	} else {
		e_save = list_without_metadb(nhosts, hosts, opt_port,
		    request_op, pa);
	}
	e = gfarm_paraccess_free(pa);
	if (e_save == GFARM_ERR_NO_ERROR)
		e_save = e;

	if (!opt_plain_order)
		output_sort(opt_sort_by_loadavg ? output_cmp_by_loadavg :
		    output_cmp_by_name);

	return (e_save);
}
