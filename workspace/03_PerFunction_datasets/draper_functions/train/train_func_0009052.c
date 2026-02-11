png_image_read_colormapped(png_voidp argument)
{
   png_image_read_control *display = png_voidcast(png_image_read_control*,
      argument);
   png_imagep image = display->image;
   png_controlp control = image->opaque;
   png_structrp png_ptr = control->png_ptr;
   png_inforp info_ptr = control->info_ptr;

   int passes = 0;

   PNG_SKIP_CHUNKS(png_ptr);


   if (display->colormap_processing == PNG_CMAP_NONE)
      passes = png_set_interlace_handling(png_ptr);

   png_read_update_info(png_ptr, info_ptr);


   switch (display->colormap_processing)
   {
      case PNG_CMAP_NONE:


         if ((info_ptr->color_type == PNG_COLOR_TYPE_PALETTE ||
            info_ptr->color_type == PNG_COLOR_TYPE_GRAY) &&
            info_ptr->bit_depth == 8)
            break;

         goto bad_output;

      case PNG_CMAP_TRANS:
      case PNG_CMAP_GA:


         if (info_ptr->color_type == PNG_COLOR_TYPE_GRAY_ALPHA &&
            info_ptr->bit_depth == 8 &&
            png_ptr->screen_gamma == PNG_GAMMA_sRGB &&
            image->colormap_entries == 256)
            break;

         goto bad_output;

      case PNG_CMAP_RGB:

         if (info_ptr->color_type == PNG_COLOR_TYPE_RGB &&
            info_ptr->bit_depth == 8 &&
            png_ptr->screen_gamma == PNG_GAMMA_sRGB &&
            image->colormap_entries == 216)
            break;

         goto bad_output;

      case PNG_CMAP_RGB_ALPHA:

         if (info_ptr->color_type == PNG_COLOR_TYPE_RGB_ALPHA &&
            info_ptr->bit_depth == 8 &&
            png_ptr->screen_gamma == PNG_GAMMA_sRGB &&
            image->colormap_entries == 244 )
            break;


      default:
      bad_output:
         png_error(png_ptr, "bad color-map processing (internal error)");
   }


   {
      png_voidp first_row = display->buffer;
      ptrdiff_t row_bytes = display->row_stride;


      if (row_bytes < 0)
      {
         char *ptr = png_voidcast(char*, first_row);
         ptr += (image->height-1) * (-row_bytes);
         first_row = png_voidcast(png_voidp, ptr);
      }

      display->first_row = first_row;
      display->row_bytes = row_bytes;
   }

   if (passes == 0)
   {
      int result;
      png_voidp row = png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));

      display->local_row = row;
      result = png_safe_execute(image, png_image_read_and_map, display);
      display->local_row = NULL;
      png_free(png_ptr, row);

      return result;
   }

   else
   {
      png_alloc_size_t row_bytes = display->row_bytes;

      while (--passes >= 0)
      {
         png_uint_32      y = image->height;
         png_bytep        row = png_voidcast(png_bytep, display->first_row);

         while (y-- > 0)
         {
            png_read_row(png_ptr, row, NULL);
            row += row_bytes;
         }
      }

      return 1;
   }
}
