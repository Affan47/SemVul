download_requeue(struct download *d)
{
	download_check(d);
	file_info_check(d->file_info);

	g_return_if_fail(!FILE_INFO_FINISHED(d->file_info));
	g_return_if_fail(!DOWNLOAD_IS_QUEUED(d));
	g_return_if_fail(!DOWNLOAD_IS_VERIFYING(d));

	g_return_if_fail(d->file_info->lifecount > 0);
	download_queue(d, _("Explicitly requeued"));
}
