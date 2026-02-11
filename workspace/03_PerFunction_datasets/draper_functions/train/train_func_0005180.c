rgbe_header_init (rgbe_header *header)
{
  g_return_if_fail (header);

  header->format              = FORMAT_UNKNOWN;
  memset (header->software, '\0', G_N_ELEMENTS (header->software));

  header->exposure            = 1.0;
  header->colorcorr[OFFSET_R] = 1.0;
  header->colorcorr[OFFSET_G] = 1.0;
  header->colorcorr[OFFSET_B] = 1.0;

  header->pixel_aspect        = 1.0;

  header->x_axis.orient = header->y_axis.orient = ORIENT_UNKNOWN;
  header->x_axis.size   = header->y_axis.size   = 0;
}
