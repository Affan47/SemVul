view_slideshow_stop_func(SlideShowData *fs, gpointer data)
{
	ViewWindow *vw = data;
	GList *work;
	FileData *fd;

	vw->ss = NULL;

	work = vw->list;
	fd = image_get_fd(view_window_active_image(vw));
	while (work)
		{
		FileData *temp;

		temp = work->data;
		if (fd == temp)
			{
			vw->list_pointer = work;
			work = NULL;
			}
		else
			{
			work = work->next;
			}
		}
}
