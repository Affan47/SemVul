line_read_bgr_16_line_mode (Artec48U_Line_Reader * reader,
			    unsigned int **buffer_pointers_return)
{
  SANE_Status status;
  size_t size;
  SANE_Int pixels_per_line;
  SANE_Byte *pixel_buffer = reader->pixel_buffer;

  XDBG ((3, "line_read_bgr_16_line_mode\n"));
  size = reader->params.scan_bpl * 3;
  status = artec48u_device_read (reader->dev, pixel_buffer, &size);
  if (status != SANE_STATUS_GOOD)
    return status;

  pixels_per_line = reader->pixels_per_line;
  unpack_16_le_mono (pixel_buffer,
		     DELAY_BUFFER_WRITE_PTR (&reader->b_delay),
		     pixels_per_line);
  pixel_buffer += reader->params.scan_bpl;
  unpack_16_le_mono (pixel_buffer,
		     DELAY_BUFFER_WRITE_PTR (&reader->g_delay),
		     pixels_per_line);
  pixel_buffer += reader->params.scan_bpl;
  unpack_16_le_mono (pixel_buffer,
		     DELAY_BUFFER_WRITE_PTR (&reader->r_delay),
		     pixels_per_line);

  buffer_pointers_return[0] = DELAY_BUFFER_READ_PTR (&reader->r_delay);
  buffer_pointers_return[1] = DELAY_BUFFER_READ_PTR (&reader->g_delay);
  buffer_pointers_return[2] = DELAY_BUFFER_READ_PTR (&reader->b_delay);

  DELAY_BUFFER_STEP (&reader->r_delay);
  DELAY_BUFFER_STEP (&reader->g_delay);
  DELAY_BUFFER_STEP (&reader->b_delay);

  return SANE_STATUS_GOOD;
}
