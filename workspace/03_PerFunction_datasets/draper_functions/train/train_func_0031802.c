ComputeInverseBestFitFromMinMax( double intercept, double slope, double _min, double _max)
{
  PixelFormat st = PixelFormat::UNKNOWN;


  double dmin = (_min - intercept ) / slope;
  double dmax = (_max - intercept ) / slope;
  assert( dmin <= dmax );
  assert( dmax <= std::numeric_limits<int64_t>::max() );
  assert( dmin >= std::numeric_limits<int64_t>::min() );


  int64_t min = (int64_t)dmin;
  int64_t max = (int64_t)dmax;
  if( min >= 0 )
    {
    if( max <= std::numeric_limits<uint8_t>::max() )
      {
      st = PixelFormat::UINT8;
      }
    else if( max <= std::numeric_limits<uint16_t>::max() )
      {
      st = PixelFormat::UINT16;
      assert( st.GetBitsAllocated() == 16 );

      if( max <= 4096 )
        {
        st.SetBitsStored( 12 );
        st.SetHighBit( 11 );
        }
      }
    else if( max <= std::numeric_limits<uint32_t>::max() )
      {
      st = PixelFormat::UINT32;
      }
    else
      {
      assert(0);
      }
    }
  else
    {
    if( max <= std::numeric_limits<int8_t>::max()
      && min >= std::numeric_limits<int8_t>::min() )
      {
      st = PixelFormat::INT8;
      }
    else if( max <= std::numeric_limits<int16_t>::max()
      && min >= std::numeric_limits<int16_t>::min() )
      {
      st = PixelFormat::INT16;
      }
    else if( max <= std::numeric_limits<int32_t>::max()
      && min >= std::numeric_limits<int32_t>::min() )
      {
      st = PixelFormat::INT32;
      }
    else
      {
      assert(0);
      }
    }

  assert( min >= PixelFormat(st).GetMin() );
  assert( max <= PixelFormat(st).GetMax() );
  assert( st != PixelFormat::UNKNOWN );
  assert( st != PixelFormat::FLOAT32 && st != PixelFormat::FLOAT16 && st != PixelFormat::FLOAT64 );
  return st;
}
