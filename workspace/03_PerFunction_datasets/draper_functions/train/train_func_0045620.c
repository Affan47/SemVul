metadata_write_queue_confirm(gboolean force_dialog, FileUtilDoneFunc done_func, gpointer done_data)
{
	GList *work;
	GList *to_approve = NULL;

	work = metadata_write_queue;
	while (work)
		{
		FileData *fd = work->data;
		work = work->next;

		if (!isname(fd->path))
			{

			metadata_write_queue_remove(fd);
			continue;
			}

		if (fd->change) continue;

		to_approve = g_list_prepend(to_approve, file_data_ref(fd));
		}

	file_util_write_metadata(NULL, to_approve, NULL, force_dialog, done_func, done_data);

	return (metadata_write_queue != NULL);
}
