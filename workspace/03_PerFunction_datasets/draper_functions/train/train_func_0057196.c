encode_row_internal( byte * dest, int destlen, const byte * source, int sourcelen )
{
  char *pout = dest;
  const char *pin = source;
  int length = sourcelen;
  while( pin != source + sourcelen )
    {
    assert( length <= sourcelen );
    assert( pin <= source + sourcelen );
    int count = count_identical_bytes(pin, length);
    if( count > 1 )
      {


      if( pout + 1 + 1 > dest + destlen ) return -1;
      *pout = (char)(-count + 1);
      assert( *pout <= -1 && *pout >= -127 );
      ++pout;
      *pout = *pin;
      ++pout;
      }
    else
      {


      count = count_nonrepetitive_bytes(pin, length);

      if( pout + count + 1 > dest + destlen ) return -1;
      *pout = (char)(count - 1);
      assert( *pout != -128 && *pout+1 == count );
      assert( *pout >= 0 );
      ++pout;
      memcpy(pout, pin, count);
      pout += count;
      }

    pin += count;

    assert( count <= length );
    length -= count;
    }
  return pout - dest;
}
