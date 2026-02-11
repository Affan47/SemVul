mono_tramp_info_cleanup (void)
{
	GSList *l;

	for (l = tramp_infos; l; l = l->next) {
		MonoTrampInfo *info = (MonoTrampInfo *)l->data;

		mono_tramp_info_free (info);
	}
	g_slist_free (tramp_infos);
}
