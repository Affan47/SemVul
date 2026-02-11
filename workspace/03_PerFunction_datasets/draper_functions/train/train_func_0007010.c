file_util_finalize_all(UtilityData *ud)
{
	GList *work = ud->flist;

	if (ud->phase == UTILITY_PHASE_CANCEL) return;
	if (ud->phase == UTILITY_PHASE_DONE && !ud->finalize_func) return;
	if (ud->phase == UTILITY_PHASE_DISCARD && !ud->discard_func) return;

	while (work)
		{
		FileData *fd = work->data;
		work = work->next;
		if (ud->phase == UTILITY_PHASE_DONE) ud->finalize_func(fd);
		else if (ud->phase == UTILITY_PHASE_DISCARD) ud->discard_func(fd);
		}
}
