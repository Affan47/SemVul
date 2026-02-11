SwapBytesIfNecessary(void *buffer,
                                     SizeType _numberOfPixels)
{

  size_t numberOfPixels = static_cast< size_t >( _numberOfPixels );

  if ( m_ByteOrder == LittleEndian )
    {
    switch ( m_ComponentType )
      {
      case CHAR:
        ByteSwapper< char >::SwapRangeFromSystemToLittleEndian( (char *)buffer,
                                                                numberOfPixels );
        break;
      case UCHAR:
        ByteSwapper< unsigned char >::SwapRangeFromSystemToLittleEndian
          ( (unsigned char *)buffer, numberOfPixels );
        break;
      case SHORT:
        ByteSwapper< short >::SwapRangeFromSystemToLittleEndian
          ( (short *)buffer, numberOfPixels );
        break;
      case USHORT:
        ByteSwapper< unsigned short >::SwapRangeFromSystemToLittleEndian
          ( (unsigned short *)buffer, numberOfPixels );
        break;
      case INT:
        ByteSwapper< int >::SwapRangeFromSystemToLittleEndian
          ( (int *)buffer, numberOfPixels );
        break;
      case UINT:
        ByteSwapper< unsigned int >::SwapRangeFromSystemToLittleEndian
          ( (unsigned int *)buffer, numberOfPixels );
        break;
      case LONG:
        ByteSwapper< long >::SwapRangeFromSystemToLittleEndian
          ( (long *)buffer, numberOfPixels );
        break;
      case ULONG:
        ByteSwapper< unsigned long >::SwapRangeFromSystemToLittleEndian
          ( (unsigned long *)buffer, numberOfPixels );
        break;
      case FLOAT:
        ByteSwapper< float >::SwapRangeFromSystemToLittleEndian( (float *)buffer,
                                                                 numberOfPixels );
        break;
      case DOUBLE:
        ByteSwapper< double >::SwapRangeFromSystemToLittleEndian
          ( (double *)buffer, numberOfPixels );
        break;
      default:
        itkExceptionMacro(<< "Pixel Type Unknown");
      }
    }
  else
    {
    switch ( m_ComponentType )
      {
      case CHAR:
        ByteSwapper< char >::SwapRangeFromSystemToBigEndian( (char *)buffer,
                                                             numberOfPixels );
        break;
      case UCHAR:
        ByteSwapper< unsigned char >::SwapRangeFromSystemToBigEndian
          ( (unsigned char *)buffer, numberOfPixels );
        break;
      case SHORT:
        ByteSwapper< short >::SwapRangeFromSystemToBigEndian
          ( (short *)buffer, numberOfPixels );
        break;
      case USHORT:
        ByteSwapper< unsigned short >::SwapRangeFromSystemToBigEndian
          ( (unsigned short *)buffer, numberOfPixels );
        break;
      case INT:
        ByteSwapper< int >::SwapRangeFromSystemToBigEndian
          ( (int *)buffer, numberOfPixels );
        break;
      case UINT:
        ByteSwapper< unsigned int >::SwapRangeFromSystemToBigEndian
          ( (unsigned int *)buffer, numberOfPixels );
        break;
      case LONG:
        ByteSwapper< long >::SwapRangeFromSystemToBigEndian
          ( (long *)buffer, numberOfPixels );
        break;
      case ULONG:
        ByteSwapper< unsigned long >::SwapRangeFromSystemToBigEndian
          ( (unsigned long *)buffer, numberOfPixels );
        break;
      case FLOAT:
        ByteSwapper< float >::SwapRangeFromSystemToBigEndian
          ( (float *)buffer, numberOfPixels );
        break;
      case DOUBLE:
        ByteSwapper< double >::SwapRangeFromSystemToBigEndian
          ( (double *)buffer, numberOfPixels );
        break;
      default:
        itkExceptionMacro(<< "Pixel Type Unknown");
      }
    }
}
