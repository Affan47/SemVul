laccount_cmp(const void * a, const void * b)
	{
		const eb_local_account *ca=a, *cb=b;
		int cmp = 0;
		if(cmp == 0)
			cmp = strcasecmp(ca->handle, cb->handle);
		if(cmp == 0)
			cmp = strcasecmp(get_service_name(ca->service_id), get_service_name(cb->service_id));

		return cmp;
	}
