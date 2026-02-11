readSBits( int numBits ) throw ( exception ) {

  long uBits = readUBits( numBits );
	if( numBits > 0 ) {

	  if( ( uBits & ( 1L << (numBits - 1 ) ) ) != 0 ) {

		uBits |= -1L << numBits;
	  }
	}
  return static_cast< int >( uBits );
}
