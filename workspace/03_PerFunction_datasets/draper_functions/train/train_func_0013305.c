EncodeArray( unsigned char *input, size_t sizeInBytes, RakNet::BitStream * output )
{
	unsigned counter;


	for ( counter = 0; counter < sizeInBytes; counter++ )
	{
		output->WriteBits( encodingTable[ input[ counter ] ].encoding, encodingTable[ input[ counter ] ].bitLength, false );
	}


	if ( output->GetNumberOfBitsUsed() % 8 != 0 )
	{

		unsigned char remainingBits = (unsigned char) ( 8 - ( output->GetNumberOfBitsUsed() % 8 ) );

		for ( counter = 0; counter < 256; counter++ )
			if ( encodingTable[ counter ].bitLength > remainingBits )
			{
				output->WriteBits( encodingTable[ counter ].encoding, remainingBits, false );
				break;
			}

#ifdef _DEBUG
			RakAssert( counter != 256 );

#endif

	}
}
