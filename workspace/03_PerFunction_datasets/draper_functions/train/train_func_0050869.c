gdata_youtube_service_get_categories_finish (GDataYouTubeService *self, GAsyncResult *async_result, GError **error)
{
	GSimpleAsyncResult *result = G_SIMPLE_ASYNC_RESULT (async_result);
	GDataAPPCategories *categories;

	g_return_val_if_fail (GDATA_IS_YOUTUBE_SERVICE (self), NULL);
	g_return_val_if_fail (G_IS_ASYNC_RESULT (async_result), NULL);
	g_return_val_if_fail (error == NULL || *error == NULL, NULL);

	g_warn_if_fail (g_simple_async_result_get_source_tag (result) == gdata_youtube_service_get_categories_async);

	if (g_simple_async_result_propagate_error (result, error) == TRUE)
		return NULL;

	categories = g_simple_async_result_get_op_res_gpointer (result);
	if (categories != NULL)
		return g_object_ref (categories);
	return NULL;
}
