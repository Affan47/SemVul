writeImageFile( char pixelBuffer[static WIDTH*HEIGHT], int picNum )
{

  char name[50];
  sprintf(name, "%d.png", picNum );
  FILE *fp = fopen( name, "wb" );

  png_structp png_ptr = png_create_write_struct
    (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
      return;

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
      png_destroy_write_struct(&png_ptr,
          (png_infopp)NULL);
      return;
  }


  png_init_io( png_ptr, fp );


  png_set_IHDR( png_ptr, info_ptr, WIDTH, HEIGHT, 8,
                PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT );


  png_bytep * row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * HEIGHT);
  int y;
  for(y=0; y<HEIGHT; ++y)
    row_pointers[y] = (png_byte *)(pixelBuffer + WIDTH * y);


  png_set_rows( png_ptr, info_ptr, row_pointers );


  png_write_info(png_ptr, info_ptr);
  png_write_flush(png_ptr);
  png_write_image(png_ptr, row_pointers);

  png_text source_text;
  source_text.compression = PNG_TEXT_COMPRESSION_NONE;
  source_text.key = "Source";
  source_text.text = "Nintendo Gameboy Camera";
  png_set_text(png_ptr, info_ptr, &source_text, 1);

  source_text.key = "Software";
  source_text.text = "gbcamextract";
  png_set_text(png_ptr, info_ptr, &source_text, 1);

  png_write_end(png_ptr, info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);

  fclose(fp);
}
