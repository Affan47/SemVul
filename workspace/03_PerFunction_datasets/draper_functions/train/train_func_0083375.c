pixel ( PixelPacket* rep_, PixelType pixelType_ )
{
  if ( _pixelOwn )
    delete _pixel;
  _pixel = rep_;
  _pixelOwn = false;
  _isValid = true;
  _pixelType = pixelType_;
}
