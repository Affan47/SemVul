read_png(FILE *fp, png_bytepp buffer, int32_t *bpp, int32_t *width, int32_t *height)
{
	png_structp png_ptr;
	png_infop info;
	png_uint_32 w;
	png_uint_32 h;
	png_bytep *rows;

	int bit_depth;
	int32_t color_type;

	int row;
	int rowsize;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL)
		return FALSE;

	info = png_create_info_struct(png_ptr);
	if (info == NULL)
	{
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return FALSE;
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info, NULL);
		return FALSE;
	}

	png_init_io(png_ptr, fp);

	png_read_info(png_ptr, info);
	png_get_IHDR(png_ptr, info, &w, &h, &bit_depth, &color_type, NULL, NULL, NULL);

	switch (color_type)
	{
		case PNG_COLOR_TYPE_GRAY:
			#ifdef PNG2ICNS_EXPAND_GRAY
			png_set_expand_gray_1_2_4_to_8(png_ptr);
			#else
			png_set_gray_1_2_4_to_8(png_ptr);
			#endif

			if (bit_depth == 16) {
				png_set_strip_16(png_ptr);
				bit_depth = 8;
			}

			png_set_gray_to_rgb(png_ptr);
			png_set_add_alpha(png_ptr, 0xff, PNG_FILLER_AFTER);
			break;

		case PNG_COLOR_TYPE_GRAY_ALPHA:
			#ifdef PNG2ICNS_EXPAND_GRAY
			png_set_expand_gray_1_2_4_to_8(png_ptr);
			#else
			png_set_gray_1_2_4_to_8(png_ptr);
			#endif

			if (bit_depth == 16) {
				png_set_strip_16(png_ptr);
				bit_depth = 8;
			}

			png_set_gray_to_rgb(png_ptr);
			break;

		case PNG_COLOR_TYPE_PALETTE:
			png_set_palette_to_rgb(png_ptr);

			if (png_get_valid(png_ptr, info, PNG_INFO_tRNS))
				png_set_tRNS_to_alpha(png_ptr);
			else
				png_set_add_alpha(png_ptr, 0xff, PNG_FILLER_AFTER);
			break;

		case PNG_COLOR_TYPE_RGB:
			if (bit_depth == 16) {
				png_set_strip_16(png_ptr);
				bit_depth = 8;
			}

			png_set_add_alpha(png_ptr, 0xff, PNG_FILLER_AFTER);
			break;

		case PNG_COLOR_TYPE_RGB_ALPHA:
			if (bit_depth == 16) {
				png_set_strip_16(png_ptr);
				bit_depth = 8;
			}

			break;
	}

	*width = w;
	*height = h;
	*bpp = bit_depth * 4;

	png_read_update_info(png_ptr, info);

	rowsize = png_get_rowbytes(png_ptr, info);
	rows = malloc (sizeof(png_bytep) * h);
	*buffer = malloc(rowsize * h + 8);

	rows[0] = *buffer;
	for (row = 1; row < h; row++)
	{
		rows[row] = rows[row-1] + rowsize;
	}

	png_read_image(png_ptr, rows);
	png_destroy_read_struct(&png_ptr, &info, NULL);

	free(rows);

	return TRUE;
}
