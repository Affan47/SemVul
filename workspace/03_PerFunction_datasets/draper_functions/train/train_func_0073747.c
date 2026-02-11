printCard( const uint8_t card, const int maxLen, char *string  )
{
  if( 3 > maxLen ) {
    return -1;
  }

  string[ 0 ] = rankChars[ rankOfCard( card ) ];
  string[ 1 ] = suitChars[ suitOfCard( card ) ];
  string[ 2 ] = 0;

  return 2;
}
