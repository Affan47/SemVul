operator= ( const MagickLib::PixelPacket &color_ )
{
  *_pixel = color_;
  if ( color_.opacity != OpaqueOpacity )
    _pixelType = RGBAPixel;
  else
    _pixelType = RGBPixel;
  return *this;
}
