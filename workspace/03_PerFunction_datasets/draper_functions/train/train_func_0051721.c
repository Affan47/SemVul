st_texture_cache_load_sliced_image (StTextureCache *cache,
                                    const gchar    *path,
                                    gint            grid_width,
                                    gint            grid_height,
                                    GFunc           load_callback,
                                    gpointer        user_data)
{
  AsyncImageData *data;
  GSimpleAsyncResult *result;
  ClutterActor *actor = clutter_actor_new ();

  data = g_new0 (AsyncImageData, 1);
  data->grid_width = grid_width;
  data->grid_height = grid_height;
  data->path = g_strdup (path);
  data->actor = actor;
  data->load_callback = load_callback;
  data->load_callback_data = user_data;
  g_object_ref (G_OBJECT (actor));

  result = g_simple_async_result_new (G_OBJECT (cache), on_sliced_image_loaded, data, st_texture_cache_load_sliced_image);

  g_object_set_data_full (G_OBJECT (result), "load_sliced_image", data, on_data_destroy);
  g_simple_async_result_run_in_thread (result, load_sliced_image, G_PRIORITY_DEFAULT, NULL);

  g_object_unref (result);

  return actor;
}
