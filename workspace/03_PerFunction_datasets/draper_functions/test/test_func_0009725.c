read_sign_start_block( unsigned char **ptr, unsigned char *end )
{
  size_t length;

  if( end - *ptr < 8 ) {
    fprintf( stderr, "%s: not enough bytes for sign start block\n", progname );
    return 1;
  }

  printf( "Found a signed data start block\n" );

  length = read_dword( ptr );

  printf( "  Length: %ld bytes\n", (unsigned long)length );
  printf( "  Key ID: 0x%08x\n", (unsigned int)read_dword( ptr ) );
  printf( "  Week code: 0x%08x\n", (unsigned int)read_dword( ptr ) );

  (*ptr) += length - 13;

  return 0;
}
