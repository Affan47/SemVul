findMin( GByte *pNumBits )
{
GUInt32 u32Val;
GUInt32 u32Min, u32Max;

   u32Min = valueAsUInt32( 0 );
   u32Max = u32Min;

  for( GUInt32 count = 1; count < m_nBlockCount; count++ )
  {
    u32Val = valueAsUInt32( count );
    if( u32Val < u32Min )
      u32Min = u32Val;
    else if( u32Val > u32Max )
      u32Max = u32Val;
  }

  *pNumBits = _FindNumBits( u32Max - u32Min );

  return u32Min;
}
