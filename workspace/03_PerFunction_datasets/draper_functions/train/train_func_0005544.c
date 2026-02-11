_register_front_ends(slurm_conf_frontend_t *front_end_ptr)
{
	hostlist_t hostname_list = NULL;
	hostlist_t address_list = NULL;
	char *hostname = NULL;
	char *address = NULL;
	int error_code = SLURM_SUCCESS;

	if ((front_end_ptr->frontends == NULL) ||
	    (front_end_ptr->frontends[0] == '\0'))
		return -1;

	if ((hostname_list = hostlist_create(front_end_ptr->frontends))
	     == NULL) {
		error("Unable to create FrontendNames list from %s",
		      front_end_ptr->frontends);
		error_code = errno;
		goto cleanup;
	}
	if ((address_list = hostlist_create(front_end_ptr->addresses))
	     == NULL) {
		error("Unable to create FrontendAddr list from %s",
		      front_end_ptr->addresses);
		error_code = errno;
		goto cleanup;
	}
	if (hostlist_count(address_list) != hostlist_count(hostname_list)) {
		error("Node count mismatch between FrontendNames and "
		      "FrontendAddr");
		goto cleanup;
	}

	while ((hostname = hostlist_shift(hostname_list))) {
		address = hostlist_shift(address_list);

		_push_to_hashtbls(hostname, hostname, address,
				  front_end_ptr->port, 1, 1, 1, 1, 1, 1);
		free(hostname);
		free(address);
	}


cleanup:
	if (hostname_list)
		hostlist_destroy(hostname_list);
	if (address_list)
		hostlist_destroy(address_list);
	return error_code;
}
