file_cache_remove_fd(FileCacheData *fc, FileData *fd)
{
	GList *work;
	FileCacheEntry *fe;

	if (debug_file_cache) file_cache_dump(fc);

	work = fc->list;
	while (work)
		{
		GList *current = work;
		fe = work->data;
		work = work->next;

		if (fe->fd == fd)
			{
			fc->list = g_list_delete_link(fc->list, current);

			DEBUG_1("cache remove: fc=%p %s", fc, fe->fd->path);
			fc->size -= fe->size;
			fc->release(fe->fd);
			file_data_unref(fe->fd);
			g_free(fe);
			}
		}
}
