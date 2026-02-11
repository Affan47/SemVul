thumb_loader_std_thumb_file_validate_cancel(ThumbLoaderStd *tl)
{
	ThumbValidate *tv;

	if (!tl) return;

	tv = tl->data;

	if (tv->idle_id)
		{
		g_source_remove(tv->idle_id);
		tv->idle_id = 0;
		}

	thumb_loader_std_thumb_file_validate_free(tv);
}
