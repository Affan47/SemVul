image_options_sync(void)
{
	GList *work;

	work = image_list;
	while (work)
		{
		ImageWindow *imd;

		imd = work->data;
		work = work->next;

		image_options_set(imd);
		}
}
