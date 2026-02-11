Clone() const
{
  JPEGCodec *copy = new JPEGCodec;
  ImageCodec &ic = *copy;
  ic = *this;
  assert( copy->PF == PF );

  copy->SetPixelFormat( GetPixelFormat() );
  assert( copy->BitSample == BitSample || BitSample == 0 );

  copy->Quality = Quality;

  return copy;
}
