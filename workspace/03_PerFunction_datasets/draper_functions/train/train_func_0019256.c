get_filesize (fosfat_file_t *file, const char *path)
{
  char *it = NULL;
  uint8_t bpp = 0;
  uint16_t x = 0, y = 0;

  if (g_pbm)
    it = strstr (file->name, ".image\0");
  if (!it && g_xpm)
    it = strstr (file->name, ".color\0");

  if (!it || file->att.isdir || file->att.islink || file->att.isencoded
      || !fosgra_is_image (fosfat, path))
    return file->size;

  fosgra_get_info (fosfat, path, &x, &y, &bpp);

  if (bpp == 4)
    return x * y + y + count_nb_dec (x) + count_nb_dec (y) + 14 + 16 * 12;

  return x / 8 * y + count_nb_dec (x) + count_nb_dec (y) + 5;
}
