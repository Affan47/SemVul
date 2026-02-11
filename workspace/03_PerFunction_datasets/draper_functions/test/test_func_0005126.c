thumbnail_factory_build_filename (GnomeDesktopThumbnailFactory *factory,
						const char *first_element,
						...)
{
	char       *base_dir;
	GString    *path;
	va_list     var_args;
	const char *element;

	if (factory->priv->use_xdg_dir)
		base_dir = g_build_filename (g_get_user_cache_dir (),
					     "thumbnails",
					     NULL);
	else
		base_dir = g_build_filename (g_get_home_dir (),
					     ".thumbnails",
					     NULL);
	path = g_string_new (base_dir);
	g_free (base_dir);

	va_start (var_args, first_element);
	element = first_element;
  	while (element != NULL) {
  		if (element[0] != '\0') {
  			g_string_append (path, G_DIR_SEPARATOR_S);
  			g_string_append (path, element);
  		}
		element = va_arg (var_args, const char *);
	}
	va_end (var_args);

	return g_string_free (path, FALSE);
}
