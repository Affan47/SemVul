convertToPNG(AbstractFile* imageWrapper, const unsigned int* key, const unsigned int* iv, const char* png) {
	AbstractFile* imageFile;

	FILE *fp = fopen(png, "wb");
	if(!fp)
		return -1;

	if(key != NULL) {
		imageFile = openAbstractFile2(imageWrapper, key, iv);
	} else {
		imageFile = openAbstractFile(imageWrapper);
	}
	InfoIBootIM* info = (InfoIBootIM*) (imageFile->data);

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, pngError, pngWarn);
	if (!png_ptr) {
		return -1;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		return -1;
	}

	png_init_io(png_ptr, fp);

	int color_type;
	int bytes_per_pixel;

	if(info->header.format == IBOOTIM_ARGB) {
		XLOG(3, "ARGB");
		color_type = PNG_COLOR_TYPE_RGB_ALPHA;
		bytes_per_pixel = 4;
	} else if(info->header.format == IBOOTIM_GREY) {
		XLOG(3, "Grayscale");
		color_type = PNG_COLOR_TYPE_GRAY_ALPHA;
		bytes_per_pixel = 2;
	} else {
		XLOG(3, "Unknown color type!");
		return -1;
	}

	png_set_IHDR(png_ptr, info_ptr, info->header.width, info->header.height,
		     8, color_type, PNG_INTERLACE_NONE,
		     PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	png_set_bgr(png_ptr);
	png_set_invert_alpha(png_ptr);

	png_write_info(png_ptr, info_ptr);


	uint8_t *imageBuffer = malloc(imageFile->getLength(imageFile));
	imageFile->read(imageFile, imageBuffer, imageFile->getLength(imageFile));

	png_bytepp row_pointers = (png_bytepp) malloc(sizeof(png_bytep) * info->header.height);
	int i;
	for(i = 0; i < info_ptr->height; i++) {
		row_pointers[i] = imageBuffer + (info->header.width * bytes_per_pixel * i);
	}

	png_write_image(png_ptr, row_pointers);

	png_write_end(png_ptr, NULL);

	free(imageBuffer);

	return 0;
}
