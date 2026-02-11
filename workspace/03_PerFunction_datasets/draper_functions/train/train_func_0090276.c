strprintf( const string &format, char arg ) {
  string result( format );
  size_t pos = result.find( "%c", 0 );

  if ( pos != string::npos ) {
    char buf[2] = { arg, '\0' };
    result.replace( pos, 2, buf );
  }

  return result;
}
