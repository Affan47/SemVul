layout_bar_new_image(LayoutWindow *lw)
{
	if (!layout_bar_enabled(lw)) return;

	bar_set_fd(lw->bar, layout_image_get_fd(lw));
}
