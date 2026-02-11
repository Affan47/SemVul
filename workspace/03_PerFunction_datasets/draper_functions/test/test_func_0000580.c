fosgra_get_header (fosfat_t *fosfat, const char *path, fosgra_image_h_t *header)
{
  uint8_t *buffer;
  int res, jump = 0;

  buffer = fosfat_get_buffer (fosfat, path, 0, 1);
  if (!buffer)
    return -1;


  if (strstr (path, ".image\0") && *buffer == FOSGRA_IMAGE_HEADER_BIN)
    jump = FOSGRA_IMAGE_HEADER_LENGTH_BIN;
  free (buffer);

  buffer = fosfat_get_buffer (fosfat, path, jump, FOSGRA_IMAGE_HEADER_LENGTH);
  if (!buffer)
    return -1;

  res = fosgra_header_open (buffer, header);
  free (buffer);
  return res;
}
