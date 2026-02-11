ParsePlayerId( const string &s ) const {
  int rc = -1;


  int id = CFParser::StrToNum(s);
  if ( id == 1 ) rc = PLAYER_ONE;
  else if ( id == 2 ) rc = PLAYER_TWO;
  else if ( id == 0 ) rc = PLAYER_NONE;

  return rc;
}
