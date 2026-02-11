vs_image_scale_nearest_RGBA (const VSImage * dest, const VSImage * src,
    uint8_t * tmpbuf)
{
  int acc;
  int y_increment;
  int x_increment;
  int i;
  int j;
  int prev_j;

  if (dest->height == 1)
    y_increment = 0;
  else
    y_increment = ((src->height - 1) << 16) / (dest->height - 1);

  if (dest->width == 1)
    x_increment = 0;
  else
    x_increment = ((src->width - 1) << 16) / (dest->width - 1);


  acc = 0;
  prev_j = -1;
  for (i = 0; i < dest->height; i++) {
    j = (acc + 0x8000) >> 16;

    if (j == prev_j) {
      memcpy (dest->pixels + i * dest->stride,
          dest->pixels + (i - 1) * dest->stride, dest->width * 4);
    } else {
      video_scale_orc_resample_nearest_u32 (dest->pixels + i * dest->stride,
          src->pixels + j * src->stride, 0, x_increment, dest->width);
    }

    prev_j = j;
    acc += y_increment;
  }
}
