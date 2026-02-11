pixel(const char *color_)
{
  unsigned long pixel=(unsigned long) colorPixelHashTable().lookup(color_);
  if (pixel==colorPixelHashTable().notFound()) return addColor(color_);
  return pixel;
}
