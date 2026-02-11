cam_keypoints_tracking_copy_image_to_float_image(CamFloatImage *dst, CamImage *src, int scale)
{
  register unsigned int	i;

  CamAllocateFloatImage(dst, src->width / scale, src->height / scale);
  for (i = 0 ; i < dst->ncols * dst->nrows ; ++i)
    dst->data[i] = (float)src->imageData[i * scale];
}
