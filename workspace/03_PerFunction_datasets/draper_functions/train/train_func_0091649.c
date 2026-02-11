git_fetch_download_pack(
	git_remote *remote,
	git_transfer_progress_callback progress_cb,
	void *progress_payload)
{
	git_transport *t = remote->transport;

	if(!remote->need_pack)
		return 0;

	return t->download_pack(t, remote->repo, &remote->stats, progress_cb, progress_payload);
}
