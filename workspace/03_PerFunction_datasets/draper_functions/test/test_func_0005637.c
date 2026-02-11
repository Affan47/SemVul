texture_load_data_free (gpointer p)
{
  AsyncTextureLoadData *data = p;

  if (data->icon_info)
    {
      g_object_unref (data->icon_info);
      if (data->colors)
        st_icon_colors_unref (data->colors);
    }
  else if (data->uri)
    g_free (data->uri);

  if (data->key)
    g_free (data->key);

  if (data->textures)
    g_slist_free_full (data->textures, (GDestroyNotify) g_object_unref);

  g_free (data);
}
