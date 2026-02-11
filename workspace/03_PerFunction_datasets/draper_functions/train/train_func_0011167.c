image_prebuffer_set(ImageWindow *imd, FileData *fd)
{
	if (pixbuf_renderer_get_tiles((PixbufRenderer *)imd->pr)) return;

	if (fd)
		{
		if (!file_cache_get(image_get_cache(), fd))
			{
			image_read_ahead_set(imd, fd);
			}
		}
	else
		{
		image_read_ahead_cancel(imd);
		}
}
