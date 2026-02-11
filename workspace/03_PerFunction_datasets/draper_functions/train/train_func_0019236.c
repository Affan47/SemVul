layout_image_set_fd(LayoutWindow *lw, FileData *fd)
{
	if (!layout_valid(&lw)) return;

	image_change_fd(lw->image, fd, image_zoom_get_default(lw->image));

	layout_list_sync_fd(lw, fd);
	layout_image_slideshow_continue_check(lw);
	layout_bars_new_image(lw);
}
