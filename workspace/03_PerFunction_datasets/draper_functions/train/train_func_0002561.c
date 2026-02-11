GetBufferLength() const
{
  if( PF == PixelFormat::UNKNOWN ) return 0;

  assert( NumberOfDimensions );

  if( NumberOfDimensions != Dimensions.size() )
    {
    assert( Dimensions[2] == 1 );
    }
  uint32_t len = 0;
  unsigned int mul = 1;

  std::vector<unsigned int>::const_iterator it = Dimensions.begin();
  for(; it != Dimensions.end(); ++it)
    {
    assert( *it );
    mul *= *it;
    }


  if( PF == PixelFormat::UINT12 )
    {
#if 1
    mul *= PF.GetPixelSize();
#else
    assert( PF.GetSamplesPerPixel() == 1 );
    unsigned int save = mul;
    save *= 12;
    save /= 8;
    assert( save * 8 / 12 == mul );
    mul = save;
#endif
    }
  else if( PF == PixelFormat::SINGLEBIT )
    {
    assert( PF.GetSamplesPerPixel() == 1 );
    unsigned int save = mul;
    save /= 8;
    assert( save * 8 == mul );
    mul = save;
    }
  else if( PF.GetBitsAllocated() % 8 != 0 )
    {


    assert( PF.GetSamplesPerPixel() == 1 );
    const ByteValue *bv = PixelData.GetByteValue();
    assert( bv );
    unsigned int ref = bv->GetLength() / mul;
    assert( bv->GetLength() % mul == 0 );
    mul *= ref;
    }
  else
    {
    mul *= PF.GetPixelSize();
    }
  len = mul;

  assert( len != 0 );
  return len;
}
