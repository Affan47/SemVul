gms_graphics_get_picture_details (int *width, int *height, int *is_animated)
{
  if (gms_graphics_picture_is_available ())
    {
      if (width)
        *width = gms_graphics_width;
      if (height)
        *height = gms_graphics_height;
      if (is_animated)
        *is_animated = gms_graphics_animated;

      return TRUE;
    }

  return FALSE;
}
