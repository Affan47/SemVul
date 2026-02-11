write_png(VInfo *ji, uint8_t *image, FILE *x) {
  register int y;
  png_bytep rowpointers[ji->out_height];
  png_infop info_ptr;
  png_structp png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING,
						 NULL, NULL, NULL);

  if (!png_ptr)
    return(1);
  info_ptr = png_create_info_struct (png_ptr);
  if (!info_ptr) {
    png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    return(1);
  }
  if (setjmp(png_jmpbuf(png_ptr))) {

    png_destroy_write_struct(&png_ptr, &info_ptr);
    return (1);
  }

  png_init_io (png_ptr, x);
  png_set_IHDR (png_ptr, info_ptr, ji->out_width, ji->out_height,
		8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
  png_write_info (png_ptr, info_ptr);
  for (y = 0; y < ji->out_height; y++) {
    rowpointers[y] = image + y*ji->out_width*3;
  }
  png_write_image(png_ptr, rowpointers);
  png_write_end (png_ptr, info_ptr);
  png_destroy_write_struct (&png_ptr, &info_ptr);
  return(0);
}
