pk_client_copy_non_native_then_get_tid (PkClientState *state)
{
	GFile *source;
	gchar *basename;
	gchar *path;
	GFile *destination;
	gchar *user_temp = NULL;
	GError *error = NULL;
	gboolean ret;
	guint i;


	user_temp = pk_client_get_user_temp ("native-cache", &error);
	g_debug ("using temp dir %s", user_temp);


	ret = pk_progress_set_percentage (state->progress, -1);
	if (state->progress_callback != NULL && ret) {
		state->progress_callback (state->progress,
					  PK_PROGRESS_TYPE_PERCENTAGE,
					  state->progress_user_data);
	}


	for (i=0; state->files[i] != NULL; i++) {
		ret = pk_client_is_file_native (state->files[i]);
		g_debug ("%s native=%i", state->files[i], ret);
		if (!ret) {

			basename = g_path_get_basename (state->files[i]);
			path = g_build_filename (user_temp, basename, NULL);
			g_debug ("copy from %s to %s", state->files[i], path);
			source = g_file_new_for_path (state->files[i]);
			destination = g_file_new_for_path (path);


			g_file_copy_async (source, destination, G_FILE_COPY_OVERWRITE, G_PRIORITY_DEFAULT, state->cancellable,
					   (GFileProgressCallback) pk_client_copy_progress_cb, state,
					   (GAsyncReadyCallback) pk_client_copy_native_finished_cb, state);
			g_object_unref (source);
			g_object_unref (destination);


			g_free (state->files[i]);
			state->files[i] = path;
			g_free (basename);
		}
	}
	g_free (user_temp);
}
