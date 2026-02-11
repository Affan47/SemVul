apg_shaFinal( apg_SHA_INFO *shaInfo, BYTE hash[SHA_DIGESTSIZE] )
{
  int count;
  LONG lowBitcount = shaInfo->countLo, highBitcount = shaInfo->countHi;


  count = ( int ) ( ( shaInfo->countLo >> 3 ) & 0x3F );


  ( ( BYTE * ) shaInfo->data )[ count++ ] = 0x80;


  if( count > 56 )
    {

      memset( ( BYTE * ) &shaInfo->data + count, 0, 64 - count );
#ifdef APG_LITTLE_ENDIAN
      byteReverse( shaInfo->data, SHA_BLOCKSIZE );
#endif
      shaTransform( shaInfo );


      memset( &shaInfo->data, 0, 56 );
    }
  else

    memset( ( BYTE * ) &shaInfo->data + count, 0, 56 - count );
#ifdef APG_LITTLE_ENDIAN
  byteReverse( shaInfo->data, SHA_BLOCKSIZE );
#endif


  shaInfo->data[ 14 ] = highBitcount;
  shaInfo->data[ 15 ] = lowBitcount;

  shaTransform( shaInfo );
#ifdef APG_LITTLE_ENDIAN
  byteReverse( shaInfo->data, SHA_DIGESTSIZE );
#endif

  for (count=0; count<SHA_DIGESTSIZE; count++)
    hash[count] = (BYTE) ((shaInfo->digest[count>>2]) >> (8*(3-(count & 0x3)))) & 0xff ;
}
