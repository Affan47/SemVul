file_data_sc_perform_ci(FileData *fd)
{
	GList *work;
	gboolean ret = TRUE;
	FileDataChangeType type = fd->change->type;

	if (!file_data_sc_check_ci(fd, type)) return FALSE;

	work = fd->sidecar_files;
	while (work)
		{
		FileData *sfd = work->data;

		if (!file_data_perform_ci(sfd)) ret = FALSE;
		work = work->next;
		}

	if (!file_data_perform_ci(fd)) ret = FALSE;

	return ret;
}
