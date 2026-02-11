dupe_files_add(DupeWindow *dw, CollectionData *collection, CollectInfo *info,
			   FileData *fd, gboolean recurse)
{
	DupeItem *di = NULL;

	if (info)
		{
		di = dupe_item_new(info->fd);
		}
	else if (fd)
		{
		if (isfile(fd->path))
			{
			di = dupe_item_new(fd);
			}
		else if (isdir(fd->path) && recurse)
			{
			GList *f, *d;
			if (filelist_read(fd, &f, &d))
				{
				GList *work;

				f = filelist_filter(f, FALSE);
				d = filelist_filter(d, TRUE);

				work = f;
				while (work)
					{
					dupe_files_add(dw, NULL, NULL, (FileData *)work->data, TRUE);
					work = work->next;
					}
				filelist_free(f);
				work = d;
				while (work)
					{
					dupe_files_add(dw, NULL, NULL, (FileData *)work->data, TRUE);
					work = work->next;
					}
				filelist_free(d);
				}
			}
		}

	if (!di) return;

	if (dw->second_drop)
		{
		dupe_second_add(dw, di);
		}
	else
		{
		dw->list = g_list_prepend(dw->list, di);
		}
}
