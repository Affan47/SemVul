xlib_rgb_ensure_stage (void)
{
  if (image_info->stage_buf == NULL)
    image_info->stage_buf = malloc (IMAGE_HEIGHT * STAGE_ROWSTRIDE);
  return image_info->stage_buf;
}
