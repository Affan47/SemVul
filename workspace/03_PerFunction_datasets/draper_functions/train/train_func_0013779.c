logTransaction( const Game *game, const State *state,
			   const Action *action,
			   const struct timeval *sendTime,
			   const struct timeval *recvTime,
			   FILE *file )
{
  int c, r;
  char line[ MAX_LINE_LEN ];

  c = printAction( game, action, MAX_LINE_LEN, line );
  if( c < 0 ) {

    fprintf( stderr, "ERROR: transaction message too long\n" );
    return -1;
  }

  r = snprintf( &line[ c ], MAX_LINE_LEN - c,
		" %"PRIu32" %zu.%06zu %zu.%06zu\n",
		state->handId, sendTime->tv_sec, sendTime->tv_usec,
		recvTime->tv_sec, recvTime->tv_usec );
  if( r < 0 ) {

    fprintf( stderr, "ERROR: transaction message too long\n" );
    return -1;
  }
  c += r;

  if( fwrite( line, 1, c, file ) != c ) {

    fprintf( stderr, "ERROR: could not write to transaction file\n" );
    return -1;
  }
  fflush( file );

  return c;
}
