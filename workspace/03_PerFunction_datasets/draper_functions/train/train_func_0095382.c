schedule_host_domain(const char *path, const char *domain,
	int *nhostsp, struct gfarm_host_sched_info **hostsp)
{
	gfarm_error_t e;
	struct gfm_connection *gfm_server;
	int (*compare)(const void *, const void *);

	if ((e = gfm_client_connection_and_process_acquire_by_path(path,
	    &gfm_server)) != GFARM_ERR_NO_ERROR)
		return (e);

	e = gfm_client_schedule_host_domain(gfm_server, domain,
	    nhostsp, hostsp);
	gfm_client_connection_free(gfm_server);
	if (e != GFARM_ERR_NO_ERROR)
		return (e);

#ifdef __GNUC__
	compare = NULL;
#endif
	switch (option_sort_order) {
	case SO_NAME:
		compare = !option_reverse_sort ?
		    compare_hostname : compare_hostname_r;
		break;
	case SO_SIZE:
		compare = !option_reverse_sort ?
		    compare_available_capacity : compare_available_capacity_r;
		break;
	}
	qsort(*hostsp, *nhostsp, sizeof(**hostsp), compare);
	return (e);
}
