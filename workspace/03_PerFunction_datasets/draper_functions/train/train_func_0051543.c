png_set_filler(png_structrp png_ptr, png_uint_32 filler, int filler_loc)
{
   png_debug(1, "in png_set_filler");

   if (png_ptr == NULL)
      return;


   if (png_ptr->mode & PNG_IS_READ_STRUCT)
   {
#     ifdef PNG_READ_FILLER_SUPPORTED


         png_ptr->filler = (png_uint_16)filler;
#     else
         png_app_error(png_ptr, "png_set_filler not supported on read");
         PNG_UNUSED(filler)
         return;
#     endif
   }

   else
   {
#     ifdef PNG_WRITE_FILLER_SUPPORTED


         switch (png_ptr->color_type)
         {
            case PNG_COLOR_TYPE_RGB:
               png_ptr->usr_channels = 4;
               break;

            case PNG_COLOR_TYPE_GRAY:
               if (png_ptr->bit_depth >= 8)
               {
                  png_ptr->usr_channels = 2;
                  break;
               }

               else
               {


                  png_app_error(png_ptr,
                     "png_set_filler is invalid for low bit depth gray output");
                  return;
               }

            default:
               png_app_error(png_ptr,
                  "png_set_filler: inappropriate color type");
               return;
         }
#     else
         png_app_error(png_ptr, "png_set_filler not supported on write");
         return;
#     endif
   }


   png_ptr->transformations |= PNG_FILLER;

   if (filler_loc == PNG_FILLER_AFTER)
      png_ptr->flags |= PNG_FLAG_FILLER_AFTER;

   else
      png_ptr->flags &= ~PNG_FLAG_FILLER_AFTER;
}
