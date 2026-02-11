layout_image_slideshow_continue_check(LayoutWindow *lw)
{
	if (!lw->slideshow) return FALSE;

	if (!slideshow_should_continue(lw->slideshow))
		{
		layout_image_slideshow_stop(lw);
		return FALSE;
		}

	return TRUE;
}
