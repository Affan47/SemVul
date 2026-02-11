file_util_delete_dir_prepare(UtilityData *ud, GList *flist, GList *dlist)
{
	gboolean ok = TRUE;
	GList *work;


	work = dlist;
	while (work && ok)
		{
		FileData *fd;

		fd = work->data;
		work = work->next;

		ok = file_util_delete_dir_empty_path(ud, fd, 0);
		}

	work = flist;
	if (ok && file_data_sc_add_ci_delete_list(flist))
		{
		ud->content_list = g_list_concat(filelist_copy(flist), ud->content_list);
		}
	else
		{
		ok = FALSE;
		}

	if (ok)
		{
		ok = file_data_sc_add_ci_delete(ud->dir_fd);
		}

	if (!ok)
		{
		work = ud->content_list;
		while (work)
			{
			FileData *fd;

			fd = work->data;
			work = work->next;
			file_data_sc_free_ci(fd);
			}
		}

	return ok;
}
