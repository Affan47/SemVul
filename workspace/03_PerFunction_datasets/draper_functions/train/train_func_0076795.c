view_collection_step(ViewWindow *vw, gboolean next)
{
	ImageWindow *imd = view_window_active_image(vw);
	CollectionData *cd;
	CollectInfo *info;
	CollectInfo *read_ahead_info = NULL;

	cd = image_get_collection(imd, &info);

	if (!cd || !info) return;

	if (next)
		{
		info = collection_next_by_info(cd, info);
		if (options->image.enable_read_ahead)
			{
			read_ahead_info = collection_next_by_info(cd, info);
			if (!read_ahead_info) read_ahead_info = collection_prev_by_info(cd, info);
			}
		}
	else
		{
		info = collection_prev_by_info(cd, info);
		if (options->image.enable_read_ahead)
			{
			read_ahead_info = collection_prev_by_info(cd, info);
			if (!read_ahead_info) read_ahead_info = collection_next_by_info(cd, info);
			}
		}

	if (info)
		{
		image_change_from_collection(imd, cd, info, image_zoom_get_default(imd));

		if (read_ahead_info) image_prebuffer_set(imd, read_ahead_info->fd);
		}

}
