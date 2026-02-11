facebook_service_upload_photos (FacebookService     *self,
				FacebookAlbum       *album,
				GList               *file_list,
				int                  max_resolution,
				GCancellable        *cancellable,
				GAsyncReadyCallback  callback,
				gpointer             user_data)
{
	gth_task_progress (GTH_TASK (self),
			   _("Uploading the files to the server"),
			   "",
			   TRUE,
			   0.0);

	post_photos_data_free (self->priv->post_photos);
	self->priv->post_photos = g_new0 (PostPhotosData, 1);
	self->priv->post_photos->album = _g_object_ref (album);
	self->priv->post_photos->max_resolution = CLAMP (max_resolution, FACEBOOK_MIN_IMAGE_SIZE, FACEBOOK_MAX_IMAGE_SIZE);
	self->priv->post_photos->cancellable = _g_object_ref (cancellable);
	self->priv->post_photos->callback = callback;
	self->priv->post_photos->user_data = user_data;
	self->priv->post_photos->total_size = 0;
	self->priv->post_photos->n_files = 0;

	_g_query_all_metadata_async (file_list,
				     GTH_LIST_DEFAULT,
				     "*",
				     self->priv->post_photos->cancellable,
				     upload_photos_info_ready_cb,
				     self);
}
