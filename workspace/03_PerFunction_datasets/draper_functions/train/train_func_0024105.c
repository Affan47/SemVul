layout_find_by_image(ImageWindow *imd)
{
	GList *work;

	work = layout_window_list;
	while (work)
		{
		LayoutWindow *lw = work->data;
		work = work->next;

		if (lw->image == imd) return lw;
		}

	return NULL;
}
