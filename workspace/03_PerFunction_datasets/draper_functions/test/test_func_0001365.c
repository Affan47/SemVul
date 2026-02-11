facebook_service_create_album (FacebookService     *self,
			       FacebookAlbum       *album,
			       GCancellable        *cancellable,
			       GAsyncReadyCallback  callback,
			       gpointer             user_data)
{
	OAuthAccount    *account;
	CreateAlbumData *ca_data;
	char            *uri;
	GHashTable      *data_set;
	SoupMessage     *msg;

	account = web_service_get_current_account (WEB_SERVICE (self));
	g_return_if_fail (account != NULL);

	g_return_if_fail (album != NULL);
	g_return_if_fail (album->name != NULL);

	gth_task_progress (GTH_TASK (self),
			   _("Creating the new album"),
			   NULL,
			   TRUE,
			   0.0);

	ca_data = create_album_data_new (self, album);

	uri = g_strdup_printf ("https://graph.facebook.com/%s/albums", account->id);
	data_set = g_hash_table_new (g_str_hash, g_str_equal);
	g_hash_table_insert (data_set, "name", album->name);
	if (album->description != NULL)
		g_hash_table_insert (data_set, "message", album->description);
	if (album->privacy != NULL)
		g_hash_table_insert (data_set, "privacy", album->privacy);
	_facebook_service_add_access_token (self, data_set);
	msg = soup_form_request_new_from_hash ("POST", uri, data_set);
	_web_service_send_message (WEB_SERVICE (self),
				   msg,
				   cancellable,
				   callback,
				   user_data,
				   facebook_service_create_album,
				   facebook_service_create_album_ready_cb,
				   ca_data);

	g_hash_table_destroy (data_set);
}
