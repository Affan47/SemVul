png_write_image_16bit(png_voidp argument)
{
   png_image_write_control *display = png_voidcast(png_image_write_control*,
      argument);
   png_imagep image = display->image;
   png_structrp png_ptr = image->opaque->png_ptr;

   png_const_uint_16p input_row = png_voidcast(png_const_uint_16p,
      display->first_row);
   png_uint_16p output_row = png_voidcast(png_uint_16p, display->local_row);
   png_uint_16p row_end;
   const int channels = (image->format & PNG_FORMAT_FLAG_COLOR) ? 3 : 1;
   int aindex = 0;
   png_uint_32 y = image->height;

   if (image->format & PNG_FORMAT_FLAG_ALPHA)
   {
#     ifdef PNG_SIMPLIFIED_WRITE_AFIRST_SUPPORTED
         if (image->format & PNG_FORMAT_FLAG_AFIRST)
         {
            aindex = -1;
            ++input_row;
            ++output_row;
         }

         else
#     endif
         aindex = channels;
   }

   else
      png_error(png_ptr, "png_write_image: internal call error");


   row_end = output_row + image->width * (channels+1);

   while (y-- > 0)
   {
      png_const_uint_16p in_ptr = input_row;
      png_uint_16p out_ptr = output_row;

      while (out_ptr < row_end)
      {
         const png_uint_16 alpha = in_ptr[aindex];
         png_uint_32 reciprocal = 0;
         int c;

         out_ptr[aindex] = alpha;


         if (alpha > 0 && alpha < 65535)
            reciprocal = ((0xffff<<15)+(alpha>>1))/alpha;

         c = channels;
         do
         {
            png_uint_16 component = *in_ptr++;


            if (component >= alpha)
               component = 65535;


            else if (component > 0 && alpha < 65535)
            {
               png_uint_32 calc = component * reciprocal;
               calc += 16384;
               component = (png_uint_16)(calc >> 15);
            }

            *out_ptr++ = component;
         }
         while (--c > 0);


         ++in_ptr;
         ++out_ptr;
      }

      png_write_row(png_ptr, png_voidcast(png_const_bytep, display->local_row));
      input_row += display->row_bytes/(sizeof (png_uint_16));
   }

   return 1;
}
