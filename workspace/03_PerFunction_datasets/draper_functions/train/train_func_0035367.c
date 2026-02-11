YUV_2_444 (UINT8 * input_ptr, UINT8 * output_ptr, UINT32 image_width,
	   UINT32 image_height)
{
  UINT32 i, size;
  UINT8 * Ytmp = NULL;
  UINT8 * Cbtmp = NULL;
  UINT8 * Crtmp = NULL;
  UINT8 * Buff = NULL;
  Buff =
    (UINT8 *) realloc ((UINT8 *) Buff,
		       (size_t) (image_width * image_height * 3));
  if (Buff)
    {
      memcpy (Buff, input_ptr, image_width * image_height * 3);
      Ytmp = Buff;
      Cbtmp = Buff + image_width * image_height;
      Crtmp = Buff + (image_width * image_height << 1);
      size = image_width * image_height;
      for (i = size; i > 0; i--)

	{
	  *input_ptr++ = (UINT8) * Ytmp++;
	  *input_ptr++ = (UINT8) * Cbtmp++;
	  *input_ptr++ = (UINT8) * Crtmp++;
	}
      free (Buff);
      Buff = NULL;
    }
}
