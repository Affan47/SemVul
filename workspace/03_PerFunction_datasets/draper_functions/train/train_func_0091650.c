vficon_thumb_progress_count(GList *list, gint *count, gint *done)
{
	GList *work = list;
	while (work)
		{
		IconData *id = work->data;
		FileData *fd = id->fd;
		work = work->next;

		if (fd->thumb_pixbuf) (*done)++;
		(*count)++;
		}
}
