GetScalarType() const
{
  ScalarType type = PixelFormat::UNKNOWN;
  switch( BitsAllocated )
    {
  case 0:
    type = PixelFormat::UNKNOWN;
    break;
  case 1:
    type = PixelFormat::SINGLEBIT;
    break;
  case 8:
    type = PixelFormat::UINT8;
    break;
  case 12:
    type = PixelFormat::UINT12;
    break;
  case 16:
    type = PixelFormat::UINT16;
    break;
  case 32:
    type = PixelFormat::UINT32;
    break;
  case 64:
    type = PixelFormat::UINT32;
    break;
  case 24:
    gdcmWarningMacro( "This is illegal in DICOM, assuming a RGB image" );
    type = PixelFormat::UINT8;
    assert(0);
    break;
  default:
    gdcmErrorMacro( "I have never seen this before BitsAllocated "
      << BitsAllocated );
    type = PixelFormat::UNKNOWN;

    }
  if( type != PixelFormat::UNKNOWN )
    {
    if( PixelRepresentation == 0 )
      {

      }
    else if( PixelRepresentation == 1 )
      {
      assert( type <= INT32 );

      type = ScalarType(int(type)+1);
      }
    else if( PixelRepresentation == 2 )
      {
      assert( BitsAllocated == 16 );
      return FLOAT16;
      }
    else if( PixelRepresentation == 3 )
      {
      assert( BitsAllocated == 32 );
      return FLOAT32;
      }
    else if( PixelRepresentation == 4 )
      {
      assert( BitsAllocated == 64 );
      return FLOAT64;
      }
    else
      {
      assert(0);
      }
    }
  return type;
}
