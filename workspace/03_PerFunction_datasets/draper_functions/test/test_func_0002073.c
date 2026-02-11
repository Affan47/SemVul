crop_image(Gif_Image *gfi, Gt_Crop *crop, int preserve_total_crop)
{
    Gt_Crop c;
    int j;
    uint8_t **img;

    combine_crop(&c, crop, gfi);

  if (c.w > 0 && c.h > 0) {
    img = Gif_NewArray(uint8_t *, c.h + 1);
    for (j = 0; j < c.h; j++)
      img[j] = gfi->img[c.y + j] + c.x;
    img[c.h] = 0;

    gfi->left += c.x - crop->left_offset;
    gfi->top += c.y - crop->top_offset;

  } else if (preserve_total_crop) {
    c.w = c.h = 1;
    img = Gif_NewArray(uint8_t *, c.h + 1);
    img[0] = gfi->img[0];
    img[1] = 0;
    gfi->transparent = img[0][0];

  } else {

    c.w = c.h = 0;
    img = 0;
  }

  Gif_DeleteArray(gfi->img);
  gfi->img = img;
  gfi->width = c.w;
  gfi->height = c.h;
  return gfi->img != 0;
}
