file_data_sc_add_ci(FileData *fd, FileDataChangeType type)
{
	GList *work;

	if (fd->parent) fd = fd->parent;

	if (fd->change) return FALSE;

	work = fd->sidecar_files;
	while (work)
		{
		FileData *sfd = work->data;

		if (sfd->change) return FALSE;
		work = work->next;
		}

	file_data_add_ci(fd, type, NULL, NULL);

	work = fd->sidecar_files;
	while (work)
		{
		FileData *sfd = work->data;

		file_data_add_ci(sfd, type, NULL, NULL);
		work = work->next;
		}

	return TRUE;
}
