png_output(struct export *e, char *name, struct fmt_page *pg)
{
  FILE *fp;
  int x;
  png_structp png_ptr;
  png_infop info_ptr;
  png_byte *row_pointers[WH];
  static u8 rgb8[][3]={{  0,  0,  0},
		      {255,  0,  0},
		      {  0,255,  0},
		      {255,255,  0},
		      {  0,  0,255},
		      {255,  0,255},
		      {  0,255,255},
		      {255,255,255}};
  unsigned char *colour_matrix;

  if (!(colour_matrix=malloc(WH*WW)))
    {
      export_error("cannot allocate memory");
      return -1;
    }

  prepare_colour_matrix( pg, (unsigned char *)colour_matrix);

  if (not(fp = fopen(name, "w")))
    {
      free(colour_matrix);
      export_error("cannot create file");
      return -1;
      }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
				    NULL, NULL, NULL);
  if (!png_ptr)
    {
      free(colour_matrix);
      fclose(fp);
      export_error("libpng init error");
      return -1;
    }
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    {
      png_destroy_write_struct(&png_ptr,
			       (png_infopp)NULL);
      free(colour_matrix);
      fclose(fp);
      export_error("libpng init error");
      return -1;
    }
  png_init_io(png_ptr, fp);
  png_set_compression_level(png_ptr, D->compression);
  png_set_compression_mem_level(png_ptr, 9);
  png_set_compression_window_bits(png_ptr, 15);
  png_set_IHDR(png_ptr, info_ptr, WW, WH,
	       8, PNG_COLOR_TYPE_PALETTE , PNG_INTERLACE_NONE,
	       PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_set_PLTE(png_ptr, info_ptr,(png_color*) rgb8 , 8);
  png_write_info(png_ptr, info_ptr);

  for(x=0; x<WH; x++)
    { row_pointers[x]=colour_matrix+x*WW; }
  png_write_image(png_ptr, row_pointers);
  png_write_end(png_ptr, info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);

  free(colour_matrix);
  fclose(fp);
  return 0;
}
