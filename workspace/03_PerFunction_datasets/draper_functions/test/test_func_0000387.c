layout_image_scroll(LayoutWindow *lw, gint x, gint y, gboolean connect_scroll)
{
	gdouble dx, dy;
	gint width, height, i;
	if (!layout_valid(&lw)) return;

	image_scroll(lw->image, x, y);

	if (!connect_scroll) return;

	image_get_image_size(lw->image, &width, &height);
	dx = (gdouble) x / width;
	dy = (gdouble) y / height;

	for (i = 0; i < MAX_SPLIT_IMAGES; i++)
		{
		if (lw->split_images[i] && lw->split_images[i] != lw->image)
			{
			gdouble sx, sy;
			image_get_scroll_center(lw->split_images[i], &sx, &sy);
			sx += dx;
			sy += dy;
			image_set_scroll_center(lw->split_images[i], sx, sy);
			}
		}

}
