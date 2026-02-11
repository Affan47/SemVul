GrabOverlayFromPixelData(DataSet const &ds)
{
  const unsigned int ovlength = Internal->Rows * Internal->Columns / 8;
  Internal->Data.resize( ovlength );
  if( Internal->BitsAllocated == 16 )
    {

    assert( ds.FindDataElement( Tag(0x7fe0,0x0010) ) );
    const DataElement &pixeldata = ds.GetDataElement( Tag(0x7fe0,0x0010) );
    const ByteValue *bv = pixeldata.GetByteValue();
    assert( bv );
    const char *array = bv->GetPointer();


    const unsigned int length = ovlength * 8 * 2;
    const uint16_t *p = (uint16_t*)array;
    const uint16_t *end = (uint16_t*)(array + length);

    assert( 8 * ovlength == (unsigned int)Internal->Rows * Internal->Columns );
    unsigned char * overlay = (unsigned char*)&Internal->Data[0];
    int c = 0;
    uint16_t pmask = 1 << Internal->BitPosition;
    assert( length / 2 == ovlength * 8 );
    while( p != end )
      {
      const uint16_t val = *p & pmask;
      assert( val == 0x0 || val == pmask );

      if( val )
        {
        overlay[ c / 8 ] |= (0x1 << c%8);
        }
      else
        {

        }
      ++p;
      ++c;
      }
    assert( (unsigned)c / 8 == ovlength );
    }
  else
    {
    gdcmErrorMacro( "Could not grab Overlay from image. Please report." );
    return false;
    }
  return true;
}
