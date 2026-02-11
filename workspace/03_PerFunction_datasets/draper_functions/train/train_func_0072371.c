loadFromString( char* data )
{
	if( !data )
		return false;

	u32 length = strlen(data);

	if( length < 163 )
	{
		printf("RSAKEY STRING IS TOO SHORT\n");

		return false;
	}


	char* ptr = data;

	if( memcmp(ptr,"+++++++++++++++++++++++++++++++++ START RSA KEY ++++++++++++++++++++++++++++++++\n",strlen("+++++++++++++++++++++++++++++++++ START RSA KEY ++++++++++++++++++++++++++++++++\n")) != 0 )
	{
		printf( "INVALID RSAKEY HEADER\n");
		return false;
	}

	u32 ptrIndex = strlen("+++++++++++++++++++++++++++++++++ START RSA KEY ++++++++++++++++++++++++++++++++\n");

	u32 Version;

	u32 lineLength = 0;

	char bigBuffer[2048];
	u32	 bigIndex = 0;

	char line[128];
	u8	 index = 0;
	bool endOfData = false;

	while( ptrIndex < length )
	{
		if( ptr[ptrIndex] == '?' )
		{
			if( ptr[ptrIndex+1] != '~' )
			{

				printf("RSAKEY:LOAD CORRUPTED END OF DATA SECTION MARKER %c\n", ptr[ptrIndex+1]);

				return false;
			}

			ptrIndex++;
			ptrIndex++;

			endOfData = true;
		}
		else if( ptr[ptrIndex] != '\n' )
		{
			line[index] = ptr[ptrIndex];
			index++;
			ptrIndex++;
		}
		else
		{
			memcpy(&bigBuffer[bigIndex], &line[0], index);

			bigIndex += index;

			line[index] = '\0';

			index = 0;
			ptrIndex++;

			if( endOfData )
				break;
		}
	}

	if( memcmp(&ptr[ptrIndex], "+++++++++++++++++++++++++++++++++  END  RSA KEY ++++++++++++++++++++++++++++++++\n",strlen("+++++++++++++++++++++++++++++++++  END  RSA KEY ++++++++++++++++++++++++++++++++\n")) != 0 )
	{
		printf("RSAKEY FOOTER CORRUPTED.\n");
	}

	bigBuffer[bigIndex] = '\0';

	u8* DecodedData;
	u32 dataLen;


	base64Dec(bigBuffer, bigIndex, &DecodedData, &dataLen );


	Version = *((u32*)&DecodedData[0]);
	Exponent = *((u64*)&DecodedData[4]);
	Prime.setValue( *((u64*)&DecodedData[12]) );

	return true;
}
