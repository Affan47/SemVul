WriteAuPayloadLengthInfo( HANDLE_FDK_BITSTREAM hBitStream, int AuLengthBits )
{
  int restBytes;

  if( AuLengthBits % 8 )
    return TRANSPORTENC_INVALID_AU_LENGTH;

  while( AuLengthBits >= 255*8 ) {
    FDKwriteBits( hBitStream, 255, 8 );
    AuLengthBits -= (255*8);
  }

  restBytes = (AuLengthBits) >> 3;
  FDKwriteBits( hBitStream, restBytes, 8 );

  return TRANSPORTENC_OK;
}
