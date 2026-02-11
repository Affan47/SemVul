dimensionsMess(int width, int height)
{
  if (width <= 0) {
    error("width must be greater than 0");
    return;
  }

  if (height <= 0 ) {
    error ("height must be greater than 0");
    return;
  }
  GemMan::m_width = width;
  GemMan::m_height = height;
}
