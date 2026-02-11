imImageLineCount(int width, int color_mode)
{
  if (imColorModeIsPacked(color_mode))
    return width*imColorModeDepth(color_mode);
  else
    return width;
}
