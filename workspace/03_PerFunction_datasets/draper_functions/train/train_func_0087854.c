nlmclnt_release_host(struct nlm_host *host)
{
	if (host == NULL)
		return;

	dprintk("lockd: release client host %s\n", host->h_name);

	WARN_ON_ONCE(host->h_server);

	if (atomic_dec_and_test(&host->h_count)) {
		WARN_ON_ONCE(!list_empty(&host->h_lockowners));
		WARN_ON_ONCE(!list_empty(&host->h_granted));
		WARN_ON_ONCE(!list_empty(&host->h_reclaim));

		mutex_lock(&nlm_host_mutex);
		nlm_destroy_host_locked(host);
		mutex_unlock(&nlm_host_mutex);
	}
}
