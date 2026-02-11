cam_keypoints_tracking2_copy_image_to_float_image(CamFloatImage *dst, CamImage *src, int scale)
{
  register unsigned int	x;
  register unsigned int	y;

  for (y = 0 ; y < dst->nrows ; ++y)
    for (x = 0 ; x < dst->ncols ; ++x)
      dst->data[y * dst->ncols + x] = (float)src->imageData[y * scale * src->width + x * scale];
}
