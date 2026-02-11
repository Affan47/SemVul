vficon_thumb_reset_all(ViewFile *vf)
{
	GList *work = vf->list;

	while (work)
		{
		IconData *id = work->data;
		FileData *fd = id->fd;
		if (fd->thumb_pixbuf)
			{
			g_object_unref(fd->thumb_pixbuf);
			fd->thumb_pixbuf = NULL;
			}
		work = work->next;
		}
}
