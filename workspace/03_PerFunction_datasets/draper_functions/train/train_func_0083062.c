programmer_write_rom(int port, char *romImage, deviceConfig_t devConfig)
{
   unsigned short* sp = (unsigned short*)romImage;
   unsigned short* ep = sp + devConfig.romSize;
   unsigned short pad = (unsigned short)devConfig.romPad;

   while( ep > sp && pad == *--ep )
      ;

   int in, totalWords = ++ep - sp;
   unsigned char buffer[ 5 ];

   *buffer = 7;
   write( port, buffer, 1 );

   buffer[ 0 ] = totalWords >> 8;
   buffer[ 1 ] = totalWords & 0xff;
   write( port, buffer, 2 );

   read( port, buffer, 1);
   if( 'Y' != *buffer )
   {
      DEBUG_p( "DEBUG: write rom: bad response: %c\n", *buffer );
      return -1;
   }

   while( 1 )
   {
      unsigned short address = sp - (unsigned short*)romImage;

      write( port, sp, 32 );


      printf( "Writing ROM: %d%%\r", 50 * ((char*)sp - romImage) / totalWords );
      fflush(stdout);
      sp += (32 / sizeof( *sp ));

      in = read( port, buffer, 5 );
      switch( *buffer )
      {
         case 'N':
	    printf( "\nFailed to write ROM (current address 0x%0x)\n", (unsigned int)(((char*)sp) - romImage) );
            return -3;

         case 'P':
	    puts("Writing ROM: complete");
	    return 0;

         case 'Y':
            break;

         default:
	    printf( "\nBad write response, '%c' (current address 0x%0x)\n", *buffer, (unsigned int)(((char*)sp) - romImage) );
            break;
      }
   }
}
