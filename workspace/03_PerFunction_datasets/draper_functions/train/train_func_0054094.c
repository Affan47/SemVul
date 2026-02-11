Triangle(const MagickRealType x,
  const ResizeFilter *magick_unused(resize_filter))
{


  if (x < 1.0)
    return(1.0-x);
  return(0.0);
}
