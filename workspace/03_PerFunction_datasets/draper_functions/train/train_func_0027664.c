cfs_schedule_info_release_timer (CamelFolderSummary *summary)
{
	g_return_if_fail (CAMEL_IS_FOLDER_SUMMARY (summary));

	if (is_in_memory_summary (summary))
		return;

	if (!summary->priv->timeout_handle) {
		static gboolean know_can_do = FALSE, can_do = TRUE;

		if (!know_can_do) {
			can_do = !g_getenv ("CAMEL_FREE_INFOS");
			know_can_do = TRUE;
		}


		if (can_do) {
			summary->priv->timeout_handle = g_timeout_add_seconds (
				SUMMARY_CACHE_DROP,
				(GSourceFunc) cfs_try_release_memory,
				g_object_ref (summary));
		}
	}


	summary->priv->cache_load_time = time (NULL);
}
