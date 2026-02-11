cam_keypoints_tracking2_is_in_range(CamImage *image, CamKeypointShort *point)
{
  if (point->x - 2 * point->scale >= 0 && point->y - 2 * point->scale >= 0 && point->x + 2 * point->scale < image->width && point->y + 2 * point->scale < image->height && point->scale > 0)
    return (TRUE);
  return (FALSE);
}
