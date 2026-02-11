init() {
	struct net_data *net_data;

	if (!(net_data = net_data_init(NULL)))
		goto error;
	if (!net_data->ho) {
		net_data->ho = (*net_data->irs->ho_map)(net_data->irs);
		if (!net_data->ho || !net_data->res) {
  error:
			errno = EIO;
			if (net_data && net_data->res)
				RES_SET_H_ERRNO(net_data->res, NETDB_INTERNAL);
			return (NULL);
		}

		(*net_data->ho->res_set)(net_data->ho, net_data->res, NULL);
	}

	return (net_data);
}
