png_write_IDAT(png_structp png_ptr, png_bytep data, png_size_t length)
{
   png_debug(1, "in png_write_IDAT");

#ifdef PNG_WRITE_OPTIMIZE_CMF_SUPPORTED
   if (!(png_ptr->mode & PNG_HAVE_IDAT) &&
       png_ptr->compression_type == PNG_COMPRESSION_TYPE_BASE)
   {


      unsigned int z_cmf = data[0];

      if ((z_cmf & 0x0f) == 8 && (z_cmf & 0xf0) <= 0x70)
      {


         if (length >= 2 &&
             png_ptr->height < 16384 && png_ptr->width < 16384)
         {


            unsigned int z_cinfo;
            unsigned int half_z_window_size;
            png_uint_32 uncompressed_idat_size = png_ptr->height *
                ((png_ptr->width *
                png_ptr->channels * png_ptr->bit_depth + 15) >> 3);


            if (png_ptr->interlaced)
               uncompressed_idat_size += ((png_ptr->height + 7)/8) *
                   (png_ptr->bit_depth < 8 ? 12 : 6);

            z_cinfo = z_cmf >> 4;
            half_z_window_size = 1 << (z_cinfo + 7);

            while (uncompressed_idat_size <= half_z_window_size &&
                half_z_window_size >= 256)
            {
               z_cinfo--;
               half_z_window_size >>= 1;
            }

            z_cmf = (z_cmf & 0x0f) | (z_cinfo << 4);

            if (data[0] != z_cmf)
            {
               int tmp;
               data[0] = (png_byte)z_cmf;
               tmp = data[1] & 0xe0;
               tmp += 0x1f - ((z_cmf << 8) + tmp) % 0x1f;
               data[1] = (png_byte)tmp;
            }
         }
      }

      else
         png_error(png_ptr,
             "Invalid zlib compression method or flags in IDAT");
   }
#endif

   png_write_complete_chunk(png_ptr, png_IDAT, data, length);
   png_ptr->mode |= PNG_HAVE_IDAT;


   png_ptr->zstream.next_out = png_ptr->zbuf;
   png_ptr->zstream.avail_out = (uInt)png_ptr->zbuf_size;
}
