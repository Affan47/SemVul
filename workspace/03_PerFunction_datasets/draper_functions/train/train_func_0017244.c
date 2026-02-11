dump_video_memory(
  const unsigned char *video_memory,
  const struct fb_var_screeninfo *info,
  const struct fb_cmap *colormap,
  size_t line_length,
  FILE *fp
)
{
  unsigned int x, y;
  const size_t bytes_per_pixel = (info->bits_per_pixel + 7) / 8;
  unsigned char *row = malloc(info->xres * 3);
  if (row == NULL)
    posix_error("malloc failed");

  fprintf(fp, "P6 %" PRIu32 " %" PRIu32 " 255\n", info->xres, info->yres);
  for (y = 0; y < info->yres; y++)
  {
    const unsigned char *current;
    current = video_memory + (y + info->yoffset) * line_length + info->xoffset * bytes_per_pixel;
    for (x = 0; x < info->xres; x++)
    {
      unsigned int i;
      unsigned int pixel = 0;
      switch (bytes_per_pixel)
      {


        case 4:
          pixel = le32toh(*((uint32_t *) current));
          current += 4;
          break;
        case 2:
          pixel = le16toh(*((uint16_t *) current));
          current += 2;
          break;
        default:
          for (i = 0; i < bytes_per_pixel; i++)
          {
            pixel |= current[0] << (i * 8);
            current++;
          }
          break;
      }
      row[x * 3 + 0] = get_color(pixel, &info->red, colormap->red);
      row[x * 3 + 1] = get_color(pixel, &info->green, colormap->green);
      row[x * 3 + 2] = get_color(pixel, &info->blue, colormap->blue);
    }
    if (fwrite(row, 1, info->xres * 3, fp) != info->xres * 3)
      posix_error("Write error");
  }

  free(row);
}
