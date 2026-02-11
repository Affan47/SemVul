Write( const char* inputByteArray, const unsigned int numberOfBytes )
{
	if (numberOfBytes==0)
		return;


	if ((numberOfBitsUsed & 7) == 0)
	{
		AddBitsAndReallocate( BYTES_TO_BITS(numberOfBytes) );
		memcpy(data+BITS_TO_BYTES(numberOfBitsUsed), inputByteArray, (size_t) numberOfBytes);
		numberOfBitsUsed+=BYTES_TO_BITS(numberOfBytes);
	}
	else
	{
		WriteBits( ( unsigned char* ) inputByteArray, numberOfBytes * 8, true );
	}

}
