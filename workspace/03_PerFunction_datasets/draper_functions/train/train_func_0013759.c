next_host_state(struct hlist_head *cache,
					struct nsm_handle *nsm,
					const struct nlm_reboot *info)
{
	struct nlm_host *host;
	struct hlist_head *chain;

	mutex_lock(&nlm_host_mutex);
	for_each_host(host, chain, cache) {
		if (host->h_nsmhandle == nsm
		    && host->h_nsmstate != info->state) {
			host->h_nsmstate = info->state;
			host->h_state++;

			nlm_get_host(host);
			mutex_unlock(&nlm_host_mutex);
			return host;
		}
	}

	mutex_unlock(&nlm_host_mutex);
	return NULL;
}
