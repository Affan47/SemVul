png_read_data_from_mem( png_structp png_ptr,
				   png_bytep data,
				   png_size_t length)
{
  fl_png_memory *png_mem_data = (fl_png_memory*)png_get_io_ptr(png_ptr);
  if (png_mem_data->current + length > png_mem_data->last) {
    png_error(png_mem_data->pp, "Invalid attempt to read row data");
    return;
  }

  memcpy (data, png_mem_data->current, length);

  png_mem_data->current += length;
}
