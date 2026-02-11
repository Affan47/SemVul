ParseSection( ifstream &in,
    const string *opt, unsigned long &line ) {
  int rc = 0;
  size_t pos;
  string buf, val;

  pairs.clear();

  while ( !in.eof() ) {
    getline( in, buf );
    ++line;
    RemWhitespace( buf );

    if ( buf.size() == 0 ) break;
    else if ( buf[0] != '#' ) {
      pos = buf.find( '=' );
      if ( pos == string::npos ) {
        cerr << "Syntax error in line " << line << ": '=' missing" << endl;
        rc = 1;
        break;
      }
      val = buf.substr( pos+1 );
      buf.erase( pos );
      RemWhitespace( buf );
      RemWhitespace( val );

      pairs.push_back( pair<string, string>( buf, val ) );
    }
  }

  return rc;
}
