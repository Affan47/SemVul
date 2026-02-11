picture_gallery_set_path (EPictureGallery *gallery,
                          const gchar *path)
{
	g_return_if_fail (E_IS_PICTURE_GALLERY (gallery));
	g_return_if_fail (gallery->priv != NULL);

	g_free (gallery->priv->path);

	if (!path || !*path || !g_file_test (path, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_DIR))
		gallery->priv->path = g_strdup (g_get_user_special_dir (G_USER_DIRECTORY_PICTURES));
	else
		gallery->priv->path = g_strdup (path);
}
