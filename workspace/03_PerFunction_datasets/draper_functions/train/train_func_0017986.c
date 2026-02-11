fimc_color_format_get_component_height (FimcColorFormat format, int c,
    int height)
{
  switch (format) {
    case FIMC_COLOR_FORMAT_RGB32:
      return height;
    case FIMC_COLOR_FORMAT_YUV420SPT:
    case FIMC_COLOR_FORMAT_YUV420SP:
    case FIMC_COLOR_FORMAT_YUV420P:
      if (c == 0)
        return height;
      else
        return (height + 1) / 2;
    default:
      break;
  }

  return -1;
}
