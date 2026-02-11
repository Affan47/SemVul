get_pixel_boundary (Avision_Scanner* s)
{
  Avision_Device* dev = s->hw;
  int boundary;

  switch (s->c_mode) {
  case AV_TRUECOLOR:
  case AV_TRUECOLOR12:
  case AV_TRUECOLOR16:
    boundary = dev->inquiry_color_boundary;
    break;
  case AV_GRAYSCALE:
  case AV_GRAYSCALE12:
  case AV_GRAYSCALE16:
    boundary = dev->inquiry_gray_boundary;
    break;
  case AV_DITHERED:
    if (dev->inquiry_asic_type != AV_ASIC_C5)
      boundary = 32;
    else
      boundary = dev->inquiry_dithered_boundary;
    break;
  case AV_THRESHOLDED:
    if (dev->inquiry_asic_type != AV_ASIC_C5)
      boundary = 32;
    else
      boundary = dev->inquiry_thresholded_boundary;
    break;
  default:
    boundary = 8;
  }

  return boundary;
}
