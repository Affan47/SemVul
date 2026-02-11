layout_image_get_fd_list(LayoutWindow *lw)
{
	GList *list = NULL;
	FileData *fd = layout_image_get_fd(lw);

	if (fd)
		{
		if (lw->vf)

			list = vf_selection_get_one(lw->vf, fd);
		else
			list = g_list_append(NULL, file_data_ref(fd));
		}

	return list;
}
