write_zimage_to_jpeg(z_image *image, z_file *out, int color_space)
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  int row_buf_size;
  JSAMPARRAY row_buf;
  JSAMPROW jsamplerow;
  int sample_index;
  uint32_t i;
  int j;
  uint8_t *img_data_ptr;
  J_COLOR_SPACE jpeg_color_space;

  if (image == NULL)
    return;

  if (color_space == COLORSPACE_JCS_CMYK)
    return;

  if (color_space == COLORSPACE_JCS_YCCK)
    return;

  if (color_space == COLORSPACE_JCS_UNKNOWN)
    return;

  img_data_ptr = image->data;

  if (
      (color_space == COLORSPACE_JCS_RGB)
      ||
      (color_space == COLORSPACE_JCS_GRAYSCALE)
      ||
      (color_space == COLORSPACE_JCS_YCbCr)
     )
  {
    if (color_space == COLORSPACE_JCS_RGB)
      jpeg_color_space = JCS_RGB;
    else if (color_space == COLORSPACE_JCS_GRAYSCALE)
      jpeg_color_space = JCS_GRAYSCALE;
    else if (color_space == COLORSPACE_JCS_YCbCr)
      jpeg_color_space = JCS_YCbCr;
    else
      return;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, fsi->get_stdio_stream(out));

    cinfo.image_width = image->width;
    cinfo.image_height = image->height;

    if (image->image_type == DRILBO_IMAGE_TYPE_RGB)
    {
      cinfo.input_components = 3;
      cinfo.in_color_space = JCS_RGB;

      jpeg_set_defaults(&cinfo);

      jpeg_set_colorspace(&cinfo, jpeg_color_space);

      jpeg_start_compress(&cinfo, TRUE);

      row_buf_size = image->width * cinfo.input_components;
      row_buf= (*cinfo.mem->alloc_sarray)
        ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_buf_size, 1);
      jsamplerow = row_buf[0];

      while (cinfo.next_scanline < cinfo.image_height)
      {


        for (i=0, sample_index=0; i<image->width; i++)
        {
          for (j=0; j<cinfo.input_components; j++)
          {
            jsamplerow[sample_index++] = *img_data_ptr;
            img_data_ptr++;
          }
        }

        jpeg_write_scanlines(&cinfo, row_buf, 1);
      }

      jpeg_finish_compress(&cinfo);
      jpeg_destroy_compress(&cinfo);
    }
  }
}
