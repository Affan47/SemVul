download_forget(struct download *d, bool unavailable)
{
	download_check(d);

	if (DOWNLOAD_IS_STOPPED(d))
		return;

	if (DOWNLOAD_IS_QUEUED(d))
		download_unqueue(d, FALSE);

	if (unavailable)
		download_unavailable(d, GTA_DL_ABORTED, no_reason);
	else
		download_stop(d, GTA_DL_ABORTED, no_reason);
}
