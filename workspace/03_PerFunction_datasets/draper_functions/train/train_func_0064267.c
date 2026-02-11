post_photos_data_free (PostPhotosData *post_photos)
{
	if (post_photos == NULL)
		return;
	_g_object_unref (post_photos->cancellable);
	_g_object_list_unref (post_photos->file_list);
	_g_object_unref (post_photos->album);
	g_free (post_photos);
}
