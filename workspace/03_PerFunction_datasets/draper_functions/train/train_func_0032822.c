png_write_chunk_start(png_structp png_ptr, png_bytep chunk_name,
   png_uint_32 length)
{
   png_byte buf[4];
   png_debug2(0, "Writing %s chunk (%lu bytes)\n", chunk_name, length);
   if(png_ptr == NULL) return;


   png_save_uint_32(buf, length);
   png_write_data(png_ptr, buf, (png_size_t)4);


   png_write_data(png_ptr, chunk_name, (png_size_t)4);

   png_reset_crc(png_ptr);
   png_calculate_crc(png_ptr, chunk_name, (png_size_t)4);
}
