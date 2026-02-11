ReadS( int size ) {
  string str;

  for ( int i = 0; i < size; ++i )
    str += Read8();

  return str;
}
