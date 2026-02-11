file_util_delete_dir_empty_path(UtilityData *ud, FileData *fd, gint level)
{
	GList *dlist;
	GList *flist;
	GList *work;

	gboolean ok = TRUE;

	DEBUG_1("deltree into: %s", fd->path);

	level++;
	if (level > UTILITY_DELETE_MAX_DEPTH)
		{
		log_printf("folder recursion depth past %d, giving up\n", UTILITY_DELETE_MAX_DEPTH);

		return 0;
		}

	if (!filelist_read_lstat(fd, &flist, &dlist))
		{

		return 0;
		}

	if (ok)
		{
		ok = file_data_sc_add_ci_delete(fd);
		if (ok)
			{
			ud->content_list = g_list_prepend(ud->content_list, fd);
			}

		}

	work = dlist;
	while (work && ok)
		{
		FileData *lfd;

		lfd = work->data;
		work = work->next;

		ok = file_util_delete_dir_empty_path(ud, lfd, level);
		}

	work = flist;
	while (work && ok)
		{
		FileData *lfd;

		lfd = work->data;
		work = work->next;

		DEBUG_1("deltree child: %s", lfd->path);

		ok = file_data_sc_add_ci_delete(lfd);
		if (ok)
			{
			ud->content_list = g_list_prepend(ud->content_list, lfd);
			}

		}

	filelist_free(dlist);
	filelist_free(flist);


	DEBUG_1("deltree done: %s", fd->path);

	return ok;
}
