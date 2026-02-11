file_data_disable_grouping_list(GList *fd_list, gboolean disable)
{
	GList *work;

	work = fd_list;
	while (work)
		{
		FileData *fd = work->data;

		file_data_disable_grouping(fd, disable);
		work = work->next;
		}
}
