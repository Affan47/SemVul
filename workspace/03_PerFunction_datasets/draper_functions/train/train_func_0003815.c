setUpNewHand( const Game *game, const uint8_t fixedSeats,
			 uint32_t *handId, uint8_t *player0Seat,
			 rng_state_t *rng, ErrorInfo *errorInfo, State *state )
{
  ++( *handId );


  if( !fixedSeats ) {

    *player0Seat = ( *player0Seat + 1 ) % game->numPlayers;
  }

  if( checkErrorNewHand( game, errorInfo ) < 0 ) {

    fprintf( stderr, "ERROR: unexpected game\n" );
    return -1;
  }
  initState( game, *handId, state );
  dealCards( game, rng, state );

  return 0;
}
