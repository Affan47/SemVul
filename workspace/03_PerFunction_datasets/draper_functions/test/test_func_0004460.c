flickr_service_list_photos (FlickrService       *self,
			    FlickrPhotoset      *photoset,
			    const char          *extras,
			    GCancellable        *cancellable,
			    GAsyncReadyCallback  callback,
			    gpointer             user_data)
{
	FlickrListPhotosData *data;

	data = g_new0 (FlickrListPhotosData, 1);
	data->self = _g_object_ref (self);
	data->photoset = _g_object_ref (photoset);
	data->extras = g_strdup (extras);
	data->cancellable = _g_object_ref (cancellable);
	data->callback = callback;
	data->user_data = user_data;
	data->photos = NULL;
	data->position = 0;

	flickr_service_list_photoset_page (data, 1);
}
