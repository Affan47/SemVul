read_png_options (const char *thumbnail_filename)
{
	GHashTable  *options;
	png_structp  png_ptr;
        png_infop    info_ptr;
        FILE        *f;
        png_textp    text_ptr;
	int          num_texts;

	options = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

	png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL)
		return options;

	info_ptr = png_create_info_struct (png_ptr);
	if (info_ptr == NULL) {
		png_destroy_read_struct (&png_ptr, NULL, NULL);
		return options;
	}

	f = fopen (thumbnail_filename, "r");
	if (f == NULL) {
		png_destroy_read_struct (&png_ptr, &info_ptr, NULL);
		return options;
	}

	png_init_io (png_ptr, f);
	png_read_info (png_ptr, info_ptr);

	if (png_get_text (png_ptr, info_ptr, &text_ptr, &num_texts)) {
		int i;
		for (i = 0; i < num_texts; i++) {
			char *key;
			char *value;

			if (png_text_to_pixbuf_option (text_ptr[i], &key, &value))
				g_hash_table_insert (options, key, value);
		}
	}

	png_destroy_read_struct (&png_ptr, &info_ptr, NULL);
	fclose (f);

	return options;
}
