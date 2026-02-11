download_connection_register(char *label, void *handle,
			     dc_closefunc_t closefunc)
{
	download_connection_t *dcp;

	dcp = (download_connection_t *)malloc(sizeof(download_connection_t));
	if (dcp == NULL)
		return -1;

	strlcpy(dcp->dc_label, label, sizeof(dcp->dc_label));
	dcp->dc_handle = handle;
	dcp->dc_closefunc = closefunc;

	if (download_connections_h == NULL)
	{
		download_connections_h = encap_hash_new(128,
						(encap_hashfunc_t)dc_hashfunc);
		if (download_connections_h == NULL)
			return -1;
	}

	encap_hash_add(download_connections_h, dcp);

	return 0;
}
