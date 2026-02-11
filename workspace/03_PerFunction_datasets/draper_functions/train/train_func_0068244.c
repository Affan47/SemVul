nautilus_progress_info_start (NautilusProgressInfo *info)
{
	G_LOCK (progress_info);

	if (!info->started) {
		info->started = TRUE;

		info->start_at_idle = TRUE;
		queue_idle (info, TRUE);
	}

	G_UNLOCK (progress_info);
}
