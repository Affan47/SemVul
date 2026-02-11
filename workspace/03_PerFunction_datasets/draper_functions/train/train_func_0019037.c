png_image_write_init(png_imagep image)
{
   png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, image,
          png_safe_error, png_safe_warning);

   if (png_ptr != NULL)
   {
      png_infop info_ptr = png_create_info_struct(png_ptr);

      if (info_ptr != NULL)
      {
         png_controlp control = png_voidcast(png_controlp,
            png_malloc_warn(png_ptr, (sizeof *control)));

         if (control != NULL)
         {
            memset(control, 0, (sizeof *control));

            control->png_ptr = png_ptr;
            control->info_ptr = info_ptr;
            control->for_write = 1;

            image->opaque = control;
            return 1;
         }


         png_destroy_info_struct(png_ptr, &info_ptr);
      }

      png_destroy_write_struct(&png_ptr, NULL);
   }

   return png_image_error(image, "png_image_write_: out of memory");
}
