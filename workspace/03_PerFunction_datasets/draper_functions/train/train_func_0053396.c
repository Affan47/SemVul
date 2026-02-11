GetPixelSize() const
{
  uint8_t pixelsize = (uint8_t)(BitsAllocated / 8);
  if( BitsAllocated == 12 )
    {
    pixelsize = 2;
    }
  else
    {
    assert( !(BitsAllocated % 8) );
    }
  pixelsize *= SamplesPerPixel;

  return pixelsize;
}
