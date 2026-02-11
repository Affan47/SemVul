ihx32_read(FILE * hexFile, unsigned char * romImage, unsigned char *eepromImage, unsigned char *fuseImage, deviceConfig_t config ) {
	int lba = 0;
	char lineBuffer[256];
	const char* cp;
	char partBuffer[5];
	char *destImage;
	int numBytes;
	int address;
	int recType;
	int value;
	int ii;
	int done = 0;

	DEBUG_p("Preparing to read from hex file\n");

	while (done == 0) {
		fgets(lineBuffer,255,hexFile);
      cp = lineBuffer;


      if( ':' != *cp++ )
	continue;


      numBytes = (ascii2hexNybble( *cp++ ) << 4) + ascii2hexNybble( *cp++ );


      for( ii = 0, address = 0; ii < 4; ii++ )
      {
         address <<= 4;
         address += ascii2hexNybble( *cp++ );
      }


      recType = (ascii2hexNybble( *cp++ ) << 4) + ascii2hexNybble( *cp++ );

		switch(recType) {
			case 0:
				address += lba;
            if( address >= config.configStart )
            {
               if( address >= config.eepromStart )
                  destImage = eepromImage + address - config.eepromStart;
               else
                  destImage = fuseImage + 8 + address - config.configStart;

               for( ii = 0; ii < numBytes; ii++ )
                  *destImage++ = (ascii2hexNybble( *cp++ ) << 4) + ascii2hexNybble( *cp++ );
            }
            else
            {
               destImage = romImage + address;
               for( ii = 0; ii < numBytes; ii += 2, destImage += 2 )
               {
                  destImage[1] = (ascii2hexNybble( *cp++ ) << 4) + ascii2hexNybble( *cp++ );
                  destImage[0] = (ascii2hexNybble( *cp++ ) << 4) + ascii2hexNybble( *cp++ );
               }
            }
				break;
			case 1:
				done = 1;
				break;
			case 2:
				break;
			case 4:
            for( ii = 0, lba = 0; ii < 4; ii++ )
            {
               lba <<= 4;
               lba += ascii2hexNybble( *cp++ );
            }
            lba <<= 16;
				break;
		}
	}

	return 0;
}
