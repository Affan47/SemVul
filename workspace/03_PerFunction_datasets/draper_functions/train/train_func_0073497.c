st_theme_node_load_border_image (StThemeNode *node)
{
  if (node->border_slices_texture == COGL_INVALID_HANDLE)
    {
      StBorderImage *border_image;

      border_image = st_theme_node_get_border_image (node);
      if (border_image == NULL)
        goto out;

      const char *filename;
      filename = st_border_image_get_filename (border_image);
      node->border_slices_texture = st_texture_cache_load_file_to_cogl_texture (st_texture_cache_get_default (),
                                                                                filename);
      if (node->border_slices_texture == COGL_INVALID_HANDLE)
        goto out;

      node->border_slices_material = _st_create_texture_material (node->border_slices_texture);
    }

 out:
  return node->border_slices_texture != COGL_INVALID_HANDLE;
}
