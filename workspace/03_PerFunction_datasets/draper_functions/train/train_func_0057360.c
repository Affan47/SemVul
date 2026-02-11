printAction( const Game *game, const Action *action,
		 const int maxLen, char *string )
{
  int c, r;

  if( maxLen == 0 ) {
    return -1;
  }

  c = 0;

  string[ c ] = actionChars[ action->type ];
  ++c;

  if( game->bettingType == noLimitBetting && action->type == raise ) {


    r = snprintf( &string[ c ], maxLen - c, "%"PRId32, action->size );
    if( r < 0 ) {
      return -1;
    }
    c += r;
  }

  if( c >= maxLen ) {
    return -1;
  }
  string[ c ] = 0;

  return c;
}
