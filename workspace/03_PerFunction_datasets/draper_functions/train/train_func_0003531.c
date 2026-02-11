decode_gamma(png_image_read_control *display, png_uint_32 value, int encoding)
{
   if (encoding == P_FILE)
      encoding = display->file_encoding;

   if (encoding == P_NOTSET)
   {
      set_file_encoding(display);
      encoding = display->file_encoding;
   }

   switch (encoding)
   {
      case P_FILE:
         value = png_gamma_16bit_correct(value*257, display->gamma_to_linear);
         break;

      case P_sRGB:
         value = png_sRGB_table[value];
         break;

      case P_LINEAR:
         break;

      case P_LINEAR8:
         value *= 257;
         break;

      default:
         png_error(display->image->opaque->png_ptr,
            "unexpected encoding (internal error)");
         break;
   }

   return value;
}
